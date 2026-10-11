#include "gtest/gtest.h" 

#include "application/applicationdao.h"

#include "dbtestfixture.h"

namespace sun::persistence::tests 
{
    class ApplicationDaoTest : public testing::Test
    {
    protected:
        ApplicationDaoTest()
            : createDto({"Firefox", "firefox"})
            , updateDto({1, "Updated", "update"})
            , expected({1, createDto.name, createDto.processName})
            , expectedUpdated({1, updateDto.name, updateDto.processName})
        {}
    private:
        DbTestFixture db;
    protected:
        ApplicationDao applicationDao;
        CreateApplicationDto createDto;
        UpdateApplicationDto updateDto;
        Application expected;
        Application expectedUpdated;
    };

    TEST_F(ApplicationDaoTest, CreatesApplication)
    {
        Application result = applicationDao.create(createDto);
        ASSERT_EQ(result, expected);
    }

    TEST_F(ApplicationDaoTest, UpdatesApplication)
    {
        Application created = applicationDao.create(createDto);
        Application result = applicationDao.updateById(updateDto);
        ASSERT_EQ(result, expectedUpdated);
    }

    TEST_F(ApplicationDaoTest, GetsApplicationById)
    {
        Application created = applicationDao.create(createDto);
        std::optional<Application> result = applicationDao.getById(created.id);
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(created, result.value());
    }

    TEST_F(ApplicationDaoTest, DeletesApplicationById)
    {
        Application created = applicationDao.create(createDto);
        applicationDao.deleteById(created.id);
        std::optional<Application> result = applicationDao.getById(created.id);
        ASSERT_FALSE(result.has_value());
    }
} // sun::persistence::tests