#!/bin/sh
# test script for graph surveys

#ansi codes
RED='\e[1;31m'
GREEN='\e[1;32m'
BLUE='\e[1;34m'
HIGHLITE='\e[1;33;41m'
NC='\e[0m' # No Color

MAKEFILE='makefile'
#MAKEFILE='makefile.develop'

AREA51='/home/courses/cop4530p/LIB/area51'
#AREA51='../area51'


if [ $# -lt 1 ]; then
  echo -e "  ${RED} ** Error - argument required: graph file name${NC}"
  exit 1
fi

if [ ! -f $1 ] ; then
  echo -e "  ${RED} ** Error - cannot find file '$1'${NC}"
  exit 1
fi

echo -e "${BLUE}Erasing old test data ...${NC}"
rm $1.?fs_?g.local
rm $1.?fs_?g.area51

echo -e "${BLUE}Building local tests ...${NC}"
make -f ${MAKEFILE} fbfs_dg.x
make -f ${MAKEFILE} fbfs_ug.x
make -f ${MAKEFILE} fdfs_dg.x
make -f ${MAKEFILE} fdfs_ug.x

echo -e "${BLUE}Running local tests ...${NC}"
fbfs_dg.x $1 f 0 1 > $1.bfs_dg.local
fbfs_ug.x $1 f 0 1 > $1.bfs_ug.local
fdfs_dg.x $1 f 0 1 > $1.dfs_dg.local
fdfs_ug.x $1 f 0 1 > $1.dfs_ug.local

echo -e "${BLUE}Copying area51 tests ...${NC}"
cp ${AREA51}/fbfs_ug_i.x .
cp ${AREA51}/fbfs_dg_i.x .
cp ${AREA51}/fdfs_ug_i.x .
cp ${AREA51}/fdfs_dg_i.x .
chmod 700 *.x

echo -e "${BLUE}Running area51 tests ...${NC}"
fbfs_dg_i.x $1 f 0 1 > $1.bfs_dg.area51
fbfs_ug_i.x $1 f 0 1 > $1.bfs_ug.area51
fdfs_dg_i.x $1 f 0 1 > $1.dfs_dg.area51
fdfs_ug_i.x $1 f 0 1 > $1.dfs_ug.area51

echo -e "${BLUE}diff $1.bfs_dg.area51 $1.bfs_dg.local:${NC}"
diff $1.bfs_dg.area51 $1.bfs_dg.local
echo -e "${BLUE}diff $1.bfs_ug.area51 $1.bfs_ug.local:${NC}"
diff $1.bfs_ug.area51 $1.bfs_ug.local
echo -e "${BLUE}diff $1.dfs_dg.area51 $1.dfs_dg.local:${NC}"
diff $1.dfs_dg.area51 $1.dfs_dg.local
echo -e "${BLUE}diff $1.dfs_ug.area51 $1.dfs_ug.local:${NC}"
diff $1.dfs_ug.area51 $1.dfs_ug.local

if [ $# -gt 1 ]; then
  echo -e "${BLUE}complete results $1.bfs_dg.local:${NC}"
  echo -e -n " ${BLUE}press any key to contunue ...${NC}"
  read
  cat $1.bfs_dg.local
  echo -e "${BLUE}complete results $1.bfs_ug.local:${NC}"
  echo -e -n " ${BLUE}press any key to contunue ...${NC}"
  read
  cat $1.bfs_ug.local
  echo -e "${BLUE}complete results $1.dfs_dg.local:${NC}"
  echo -e -n " ${BLUE}press any key to contunue ...${NC}"
  read
  cat $1.dfs_dg.local
  echo -e "${BLUE}complete results $1.dfs_ug.local:${NC}"
  echo -e -n " ${BLUE}press any key to contunue ...${NC}"
  read
  cat $1.dfs_ug.local
fi

echo -e "${BLUE}Complete test results in $1.?fs_?g.local${NC}"
