#!/usr/bin/env bash
# The purpose of this file is to run conf/conf.sh.dist, which, in turn, auto run required DB queries

MOD_AHBOT_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"

source $MOD_AHBOT_ROOT"/conf/conf.sh.dist"