#include "gtest/gtest.h" 

#include "application/applicationdao.h"

#include "dbtestfixture.h"

namespace sun::persistence::tests 
{
    class ApplicationDaoTest : public testing::Test
    {
    protected:
        ApplicationDaoTest()
            : application({1, "Firefox", "firefox"})
        {}
    private:
        DbTestFixture db;
    protected:
        ApplicationDao applicationDao;
        Application application;
    };

    TEST_F(ApplicationDaoTest, CreatesApplication)
    {
        CreateApplicationDto dto{"Firefox", "firefox"};
        Application result = applicationDao.create(dto);
        EXPECT_EQ(result.id, application.id);
        EXPECT_EQ(result.name, application.name);
        EXPECT_EQ(result.processName, application.processName);
    }
} // sun::persistence::tests