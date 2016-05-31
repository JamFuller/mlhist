#include <limits.h>
#include "gtest/gtest.h"
#include "history.cpp"

TEST(historyUsage,failure){
  char* n_argv[] = { "mlhist","-h"};
  History history;
  testing::internal::CaptureStdout();
  history.usage("mlhist");
  std::string ActualOut = testing::internal::GetCapturedStdout();

  EXPECT_EQ("mlhist resources/resource [options] - get MarkLogic history metrics\n"
                "    -f    : format (xml|json)\n"
                "    -p    : period (raw|hour|day)\n"
                "    -s    : start date (ex. 2015-03-21T17:38:00)\n"
                "    -e    : end date (ex. 2015-03-22T17:58:00)\n"
                "    -m    : meter(s) (resource specific)\n"
                "    -r    : resource (databases|forests|servers|hosts)\n"
                "    -o    : output (graph)\n"
                "    -g    : gnuplot script\n"
                "    -v    : verbose (show http call)\n"
                "    -q    : quiet (suppress banner)\n", ActualOut);
}

TEST(historyOptions,failure){
  char* n_argv[] = { "mlhist"};

  History history;
  CommandLineArgs cmdargs = history.options(sizeof(*n_argv), n_argv);

  EXPECT_EQ(1, 1);
}