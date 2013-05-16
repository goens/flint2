#
# Regular cron jobs for the libflint2 package
#
0 4	* * *	root	[ -x /usr/bin/libflint2_maintenance ] && /usr/bin/libflint2_maintenance
