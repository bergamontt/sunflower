#include <gtest/gtest.h>

#include "applicationlist/applicationlistdao.h"
#include "application/applicationdao.h"

#include "dbtestfixture.h"

namespace sun::persistence::test
{
    class ApplicationListTest : public ::testing::Test
    {
    protected:
        ApplicationListTest()
            : createDto({"list"})
            , updateDto({1, "updated"})
            , expected({1, createDto.name})
            , updatedExpected({expected.id, updateDto.name})
            , createApp({"app", "app"})
            , application({1, createApp.name, createApp.processName})
        {}
    private:
        DbTestFixture db;
    protected:
        ApplicationListDao applicationListDao;
        ApplicationDao applicationDao;
        CreateApplicationListDto createDto;
        UpdateApplicationListDto updateDto;
        ApplicationList expected;
        ApplicationList updatedExpected;
    protected:
        CreateApplicationDto createApp;
        Application application;
    };

    TEST_F(ApplicationListTest, CreatesApplicationList)
    {
        ApplicationList created = applicationListDao.create(createDto);
        ASSERT_EQ(created, expected);
    }

    TEST_F(ApplicationListTest, UpdatesApplicationList)
    {
        ApplicationList created = applicationListDao.create(createDto);
        ApplicationList updated = applicationListDao.updateById(updateDto);
        ASSERT_EQ(updated, updatedExpected);
    }

    TEST_F(ApplicationListTest, GetsApplicationListById)
    {
        ApplicationList created = applicationListDao.create(createDto);
        std::optional<ApplicationList> found = applicationListDao.getById(created.id);
        ASSERT_TRUE(found.has_value());
        ASSERT_EQ(created, found.value());
    }

    TEST_F(ApplicationListTest, GetsNulloptApplciationListById)
    {
        std::optional<ApplicationList> found = applicationListDao.getById(expected.id);
        ASSERT_FALSE(found.has_value());
    }

    TEST_F(ApplicationListTest, DeletesApplicationListById)
    {
        ApplicationList created = applicationListDao.create(createDto);
        applicationListDao.deleteById(created.id);
        std::optional<ApplicationList> found = applicationListDao.getById(created.id);
        ASSERT_FALSE(found.has_value());
    }

    TEST_F(ApplicationListTest, GetsAllApplicationLists)
    {
        ApplicationList created = applicationListDao.create(createDto);
        QList<ApplicationList> lists = applicationListDao.getAll();
        ASSERT_EQ(lists.length(), 1);
        ASSERT_TRUE(lists.contains(created));
    }

    TEST_F(ApplicationListTest, GetsEmptyAllApplicationLists)
    {
        QList<ApplicationList> lists = applicationListDao.getAll();
        ASSERT_TRUE(lists.isEmpty());
    }

    TEST_F(ApplicationListTest, GetsEmptyInApplicationList)
    {
        ApplicationList created = applicationListDao.create(createDto);
        QList<Application> applications = applicationListDao.getAllApplications(created.id);
        ASSERT_TRUE(applications.isEmpty());
    }

    TEST_F(ApplicationListTest, AddsApplicationToApplicationList)
    {
        ApplicationList created = applicationListDao.create(createDto);
        Application createdApplication = applicationDao.create(createApp);
        applicationListDao.addApplication(created.id, createdApplication.id);
        QList<Application> applications = applicationListDao.getAllApplications(created.id);
        ASSERT_EQ(applications.length(), 1);
        ASSERT_TRUE(applications.contains(createdApplication));
    }

    TEST_F(ApplicationListTest, RemovesApplicationFromList)
    {
        ApplicationList created = applicationListDao.create(createDto);
        Application createdApplication = applicationDao.create(createApp);
        applicationListDao.addApplication(created.id, createdApplication.id);
        applicationListDao.removeApplication(created.id, createdApplication.id);
        QList<Application> applications = applicationListDao.getAllApplications(created.id);
        ASSERT_TRUE(applications.isEmpty());
    }

    TEST_F(ApplicationListTest, RemovesAllApplicationsFromList)
    {
        ApplicationList created = applicationListDao.create(createDto);
        Application createdApplication = applicationDao.create(createApp);
        applicationListDao.addApplication(created.id, createdApplication.id);
        applicationListDao.removeAllApplications(created.id);
        QList<Application> applications = applicationListDao.getAllApplications(created.id);
        ASSERT_TRUE(applications.isEmpty());
    }

    TEST_F(ApplicationListTest, GetsApplicationListsByApplicationId)
    {
        ApplicationList created = applicationListDao.create(createDto);
        Application createdApplication = applicationDao.create(createApp);
        applicationListDao.addApplication(created.id, createdApplication.id);
        QList<ApplicationList> lists = applicationListDao.getAllByApplication(createdApplication.id);
        ASSERT_EQ(lists.length(), 1);
        ASSERT_TRUE(lists.contains(created));
    }

} // sun::persistence::test