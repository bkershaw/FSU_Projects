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
cp ~cop3330p/fall14/proj1/tester.cpp .
cp ~cop3330p/fall14/proj1/testB.in .
cp ~cop3330p/fall14/proj1/segment0.data .
cp ~cop3330p/fall14/proj1/segment1.data .
cp ~cop3330p/fall14/proj1/segment2.data .
cp ~cop3330p/fall14/proj1/segment_wide.data .

cp ~cop3330p/fall14/proj1/makefile .

echo "** building project ..."
make tester.x > build.out
make tracker.x >> build.out
make trackerHybrid1.x >> build.out
make trackerHybrid2.x >> build.out

echo "** copying correct executables ..."
cp ~cop3330p/fall14/area51/tester_i.x testerCorrect.x
#cp ~lacher/cop3330/fall14/area51/tester_i.x testerCorrect.x
cp ~cop3330p/fall14/area51/tracker_i.x trackerCorrect.x
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

echo "** testing hybrid1 tracker with segment0 ..."
trackerHybrid1.x < segment0.data   > segment0.hybrid1.out
diff segment0.correct segment0.hybrid1.out > segment0.hybrid1.df

echo "** testing hybrid1 tracker with segment1 ..."
trackerHybrid1.x < segment1.data   > segment1.hybrid1.out
diff segment1.correct segment1.hybrid1.out > segment1.hybrid1.df

echo "** testing hybrid1 tracker with segment2 ..."
trackerHybrid1.x < segment2.data   > segment2.hybrid1.out
diff segment2.correct segment2.hybrid1.out > segment2.hybrid1.df

echo "** testing hybrid1 tracker with segment2 ..."
trackerCorrect.x < segment_wide.data   > segment_wide.correct
trackerHybrid1.x < segment_wide.data   > segment_wide.hybrid1.out
diff segment_wide.correct segment_wide.hybrid1.out > segment_wide.hybrid1.df

echo "** testing hybrid2 tracker with segment0 ..."
trackerHybrid2.x < segment0.data           > segment0.hybrid2.out
diff segment0.correct segment0.hybrid2.out > segment0.hybrid2.df

echo "** testing hybrid2 tracker with segment1 ..."
trackerHybrid2.x < segment1.data           > segment1.hybrid2.out
diff segment1.correct segment1.hybrid2.out > segment1.hybrid2.df

echo "** testing hybrid2 tracker with segment2 ..."
trackerHybrid2.x < segment2.data           > segment2.hybrid2.out
diff segment2.correct segment2.hybrid2.out > segment2.hybrid2.df

echo "** results of testing:"
echo "   build:"
cat build.out

echo "   tester anomolies (blank is good):"
cat testB.df

echo "   tracker segment0 anomolies (blank is good):"
cat segment0.df

echo "   tracker segment1 anomolies (blank is good):"
cat segment1.df

echo "   tracker segment2 anomolies (blank is good):"
cat segment2.df

echo "   trackerHybrid1 segment0 anomolies (blank is good):"
cat segment0.hybrid1.df

echo "   trackerHybrid1 segment1 anomolies (blank is good):"
cat segment1.hybrid1.df

echo "   trackerHybrid1 segment2 anomolies (blank is good):"
cat segment2.hybrid1.df

echo "   trackerHybrid1 segment_wide anomolies (blank is good):"
cat segment_wide.hybrid1.df

echo "   trackerHybrid2 segment0 anomolies (blank is good):"
cat segment0.hybrid2.df

echo "   trackerHybrid2 segment1 anomolies (blank is good):"
cat segment1.hybrid2.df

echo "   trackerHybrid2 segment2 anomolies (blank is good):"
cat segment2.hybrid2.df

echo "see test/*.out for complete test results"
