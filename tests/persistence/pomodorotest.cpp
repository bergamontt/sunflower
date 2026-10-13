#include <gtest/gtest.h>

#include "dbtestfixture.h"

#include "pomodoro/pomodorodao.h"
#include "applicationlist/applicationlistdao.h"

namespace sun::persistence::test
{
    class PomodoroDaoTest : public ::testing::Test
    {
    protected:
        PomodoroDaoTest()
            : createDto({3, 4, QDateTime::currentDateTime(), Pomodoro::Work})
            , updateDto({1, 5, 6, QDateTime::currentDateTime().addSecs(60), Pomodoro::Break})
            , expected({1, createDto.workDuration, createDto.breakDuration, createDto.endsAt, createDto.state})
            , updatedExpected({updateDto.id, updateDto.workDuration, updateDto.breakDuration, updateDto.endsAt, updateDto.state})
        {}
    private:
        DbTestFixture db;
    protected:
        PomodoroDao pomodoroDao;
        ApplicationListDao applicationListDao;
        CreatePomodoroDto createDto;
        UpdatePomodoroDto updateDto;
        Pomodoro expected;
        Pomodoro updatedExpected;
        CreateApplicationListDto createList;
        ApplicationList list;
    };

    TEST_F(PomodoroDaoTest, CreatesPomodoro)
    {
        Pomodoro created = pomodoroDao.create(createDto);
        ASSERT_EQ(created, expected);
    }

    TEST_F(PomodoroDaoTest, UpdatesPomodoro)
    {
        Pomodoro created = pomodoroDao.create(createDto);
        Pomodoro updated = pomodoroDao.updateById(updateDto);
        ASSERT_EQ(updated, updatedExpected);
    }

    TEST_F(PomodoroDaoTest, GetsPomodoroById)
    {
        Pomodoro created = pomodoroDao.create(createDto);
        std::optional<Pomodoro> found = pomodoroDao.getById(created.id);
        ASSERT_TRUE(found.has_value());
        ASSERT_EQ(created, found.value());
    }

    TEST_F(PomodoroDaoTest, GetsNulloptPomodoroById) 
    {
        std::optional<Pomodoro> found = pomodoroDao.getById(expected.id);
        ASSERT_FALSE(found.has_value());
    }

    TEST_F(PomodoroDaoTest, DeletesPomodoroById)
    {
        Pomodoro created = pomodoroDao.create(createDto);
        pomodoroDao.deleteById(created.id);
        std::optional<Pomodoro> found = pomodoroDao.getById(created.id);
        ASSERT_FALSE(found.has_value());
    }

    TEST_F(PomodoroDaoTest, GetsAllPomodoros)
    {
        Pomodoro created = pomodoroDao.create(createDto);
        QList<Pomodoro> Pomodoros = pomodoroDao.getAll();
        ASSERT_EQ(Pomodoros.length(), 1);
        ASSERT_TRUE(Pomodoros.contains(created));
    }

    TEST_F(PomodoroDaoTest, GetsEmptyAllPomodoros)
    {
        QList<Pomodoro> Pomodoros = pomodoroDao.getAll();
        ASSERT_TRUE(Pomodoros.isEmpty());
    }

    TEST_F(PomodoroDaoTest, AddsApplicationListToPomodoro)
    {
        Pomodoro created = pomodoroDao.create(createDto);
        ApplicationList list = applicationListDao.create(createList);
        pomodoroDao.addApplicationList(created.id, list.id);
        QList<ApplicationList> lists = pomodoroDao.getApplicationLists(created.id);
        ASSERT_EQ(lists.length(), 1);
        ASSERT_TRUE(lists.contains(list));
    }

    TEST_F(PomodoroDaoTest, GetsEmptyPomodoroApplicationLists)
    {
        Pomodoro created = pomodoroDao.create(createDto);
        QList<ApplicationList> lists = pomodoroDao.getApplicationLists(created.id);
        ASSERT_TRUE(lists.isEmpty());
    }

    TEST_F(PomodoroDaoTest, DeletesApplicationListFromPomodoro)
    {
        Pomodoro created = pomodoroDao.create(createDto);
        ApplicationList list = applicationListDao.create(createList);
        pomodoroDao.addApplicationList(created.id, list.id);
        pomodoroDao.removeApplicationList(created.id, list.id);
        QList<ApplicationList> lists = pomodoroDao.getApplicationLists(created.id);
        ASSERT_TRUE(lists.isEmpty());
    }

    TEST_F(PomodoroDaoTest, DeletesAllAplicationListsFromPomodoro)
    {
        Pomodoro created = pomodoroDao.create(createDto);
        ApplicationList list = applicationListDao.create(createList);
        pomodoroDao.addApplicationList(created.id, list.id);
        pomodoroDao.removeAllApplicationLists(created.id);
        QList<ApplicationList> lists = pomodoroDao.getApplicationLists(created.id);
        ASSERT_TRUE(lists.isEmpty());
    }
} // sun::persistence::test