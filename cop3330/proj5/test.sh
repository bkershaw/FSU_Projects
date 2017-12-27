#!/bin/sh

if test -d test; \
then echo "** erasing previous test files ... "; rm test/*; \
else echo "** creating test directory ..."; mkdir test; fi

if test -d source_backup; \
then echo "** source_backup directory exists "; \
else echo "** creating source_backup directory ..."; mkdir source_backup; fi

echo "** backing up source code ..."
cp *.h   source_backup/
cp *.cpp source_backup/

echo "** entering test directory ..."
cd test
echo "** copying project files into test directory ..."
cp ../shapes.h .
cp ../shapes.cpp .
cp ../vehicles.h .
cp ../vehicles.cpp .
cp ../verbose.cpp .
cp ../tracker.cpp .
cp ~cop3330p/LIB/proj1/tester.cpp .
cp ~cop3330p/LIB/proj1/testB.in .
cp ~cop3330p/LIB/proj1/segment0.data .
cp ~cop3330p/LIB/proj1/segment1.data .
cp ~cop3330p/LIB/proj1/segment2.data .

cp ~cop3330p/LIB/proj1/makefile .

echo "** building project ..."
make tester.x > build.out
make tracker.x >> build.out
make trackerHybrid1.x >> build.out
make trackerHybrid2.x >> build.out

echo "** copying correct executables ..."
cp ~cop3330p/LIB/area51/tester_i.x testerCorrect.x
#cp ~lacher/cop3330/LIB/area51/tester_i.x testerCorrect.x
cp ~cop3330p/LIB/area51/tracker_i.x trackerCorrect.x
chmod 700 *.x

echo "** testing classes with tester ..."
tester.x        tester.com   > testB.out
testerCorrect.x tester.com   > testB.correct
diff testB.correct testB.out > testB.df

echo "** testing tracker with segment0 ..."
tracker.x        < segment0.data   > segment0.out
trackerCorrect.x < segment0.data   > segment0.correct
diff segment0.correct segment0.out > segment0.df

echo "** testing tracker with segment1 ..."
tracker.x        < segment1.data   > segment1.out
trackerCorrect.x < segment1.data   > segment1.correct
diff segment1.correct segment1.out > segment1.df

echo "** testing tracker with segment2 ..."
tracker.x        < segment2.data   > segment2.out
trackerCorrect.x < segment2.data   > segment2.correct
diff segment2.correct segment2.out > segment2.df

echo "** results of testing:"
echo "   build:"
cat build.out

echo "   tester anomolies (blank is good):"
cat testB.df

echo "   tracker segment 0 anomolies (blank is good):"
cat segment0.df

echo "   tracker segment 1 anomolies (blank is good):"
cat segment1.df

echo "   tracker segment 2 anomolies (blank is good):"
cat segment2.df

echo "see test/*.out for complete test results"
