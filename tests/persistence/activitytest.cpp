#include <gtest/gtest.h>

#include "activity/activitydao.h"

#include "dbtestfixture.h"

#include <QDateTime>

namespace sun::persistence::test
{
    class ActivityDaoTest : public ::testing::Test
    {
    protected:
        ActivityDaoTest()
            : createDto({1, QDateTime::currentDateTime(), std::nullopt})
            , updateDto({1, QDateTime::currentDateTime().addSecs(60)})
            , expected({1, createDto.applicationId, createDto.startedAt, createDto.endedAt})
            , updatedExpected({expected.id, expected.applicationId, expected.startedAt, updateDto.endedAt})
        {}
    private:
        DbTestFixture db;
    protected:
        ActivityDao activityDao;
        CreateActivityDto createDto;
        UpdateActivityDto updateDto;
        Activity expected;
        Activity updatedExpected;
    };

    TEST_F(ActivityDaoTest, CreatesActivity)
    {
        Activity created = activityDao.create(createDto);
        ASSERT_EQ(created, expected);
    }

    TEST_F(ActivityDaoTest, GetsActivityById)
    {
        Activity created = activityDao.create(createDto);
        std::optional<Activity> found = activityDao.getById(created.id);
        ASSERT_TRUE(found.has_value());
        ASSERT_EQ(created, found.value());
    }

    TEST_F(ActivityDaoTest, GetsNulloptActivityById)
    {
        std::optional<Activity> found = activityDao.getById(expected.id);
        ASSERT_FALSE(found.has_value());
    }

    TEST_F(ActivityDaoTest, UpdatesActivity)
    {
        Activity created = activityDao.create(createDto);
        Activity updated = activityDao.updateById(updateDto);
        ASSERT_EQ(updated, updatedExpected);
    }

    TEST_F(ActivityDaoTest, DeletesActivity)
    {
        Activity created = activityDao.create(createDto);
        activityDao.deleteById(created.id);
        std::optional<Activity> found = activityDao.getById(created.id);
        ASSERT_FALSE(found.has_value());
    }
} // sun::persistence::test