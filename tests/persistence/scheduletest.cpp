#include <gtest/gtest.h>

#include "dbtestfixture.h"

#include "schedule/scheduledao.h"
#include "applicationlist/applicationlistdao.h"

namespace sun::persistence::test
{
    class ScheduleDaoTest : public ::testing::Test
    {
    protected:
        ScheduleDaoTest()
            : createDto({"name", Schedule::Type::DailyLimit, 0})
            , updateDto({1, "updated", Schedule::Type::TimeWindow, 0})
            , expected({1, createDto.name, createDto.type, createDto.repeatAt})
            , updatedExpected({updateDto.id, updateDto.name, updateDto.type, updateDto.repeatAt})
        {}
    private:
        DbTestFixture db;
    protected:
        ScheduleDao scheduleDao;
        ApplicationListDao applicationListDao;
        CreateScheduleDto createDto;
        UpdateScheduleDto updateDto;
        Schedule expected;
        Schedule updatedExpected;
    protected:
        CreateApplicationListDto createList;
        ApplicationList list;
    };

    TEST_F(ScheduleDaoTest, CreatesSchedule)
    {
        Schedule created = scheduleDao.create(createDto);
        ASSERT_EQ(created, expected);
    }

    TEST_F(ScheduleDaoTest, UpdatesSchedule)
    {
        Schedule created = scheduleDao.create(createDto);
        Schedule updated = scheduleDao.updateById(updateDto);
        ASSERT_EQ(updated, updatedExpected);
    }

    TEST_F(ScheduleDaoTest, GetsScheduleById)
    {
        Schedule created = scheduleDao.create(createDto);
        std::optional<Schedule> found = scheduleDao.getById(created.id);
        ASSERT_TRUE(found.has_value());
        ASSERT_EQ(created, found.value());
    }

    TEST_F(ScheduleDaoTest, GetsNulloptScheduleById) 
    {
        std::optional<Schedule> found = scheduleDao.getById(expected.id);
        ASSERT_FALSE(found.has_value());
    }

    TEST_F(ScheduleDaoTest, DeletesScheduleById)
    {
        Schedule created = scheduleDao.create(createDto);
        scheduleDao.deleteById(created.id);
        std::optional<Schedule> found = scheduleDao.getById(created.id);
        ASSERT_FALSE(found.has_value());
    }

    TEST_F(ScheduleDaoTest, GetsAllSchedules)
    {
        Schedule created = scheduleDao.create(createDto);
        QList<Schedule> schedules = scheduleDao.getAll();
        ASSERT_EQ(schedules.length(), 1);
        ASSERT_TRUE(schedules.contains(created));
    }

    TEST_F(ScheduleDaoTest, GetsEmptyAllSchedules)
    {
        QList<Schedule> schedules = scheduleDao.getAll();
        ASSERT_TRUE(schedules.isEmpty());
    }

    TEST_F(ScheduleDaoTest, AddsApplicationListToSchedule)
    {
        Schedule created = scheduleDao.create(createDto);
        ApplicationList list = applicationListDao.create(createList);
        scheduleDao.addApplicationList(created.id, list.id);
        QList<ApplicationList> lists = scheduleDao.getAllApplicationLists(created.id);
        ASSERT_EQ(lists.length(), 1);
        ASSERT_TRUE(lists.contains(list));
    }

    TEST_F(ScheduleDaoTest, GetsEmptyScheduleApplicationLists)
    {
        Schedule created = scheduleDao.create(createDto);
        QList<ApplicationList> lists = scheduleDao.getAllApplicationLists(created.id);
        ASSERT_TRUE(lists.isEmpty());
    }

    TEST_F(ScheduleDaoTest, DeletesApplicationListFromSchedule)
    {
        Schedule created = scheduleDao.create(createDto);
        ApplicationList list = applicationListDao.create(createList);
        scheduleDao.addApplicationList(created.id, list.id);
        scheduleDao.removeApplicationList(created.id, list.id);
        QList<ApplicationList> lists = scheduleDao.getAllApplicationLists(created.id);
        ASSERT_TRUE(lists.isEmpty());
    }

    TEST_F(ScheduleDaoTest, DeletesAllAplicationListsFromSchedule)
    {
        Schedule created = scheduleDao.create(createDto);
        ApplicationList list = applicationListDao.create(createList);
        scheduleDao.addApplicationList(created.id, list.id);
        scheduleDao.removeAllApplicationLists(created.id);
        QList<ApplicationList> lists = scheduleDao.getAllApplicationLists(created.id);
        ASSERT_TRUE(lists.isEmpty());
    }

    TEST_F(ScheduleDaoTest, GetsAllSchedulesByApplicationListId)
    {
        Schedule created = scheduleDao.create(createDto);
        ApplicationList list = applicationListDao.create(createList);
        scheduleDao.addApplicationList(created.id, list.id);
        QList<Schedule> schedules = scheduleDao.getAllByApplicationList(list.id);
        ASSERT_EQ(schedules.length(), 1);
        ASSERT_TRUE(schedules.contains(created));
    }
} // sun::persistence::test