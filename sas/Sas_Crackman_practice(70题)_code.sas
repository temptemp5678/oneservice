/**
 *
 */
* No.
* Page

/**
 *
 */
* No. 44
* Page 85

data ONE TWO SASUSER.TWO
set SASUSER.Admit;
run;

/**
 *
 */
* No. 45
* Page 86
ods csvall file='F:\SAS\raw-data\test.cvs';
proc print data=WORK.ONE;
  var Name Score Grade;
  by IdNumber;
run;
ods csvall close;

/**
 *
 */
* No. 46
* Page 86
DATA one;
	INPUT Revenue2008 Revenue2009 Revenue2010;
	DATALINES;
	1.2 1.6 2.0
;;
run;
proc print;
run;

data WORK.TWO;
  set WORK.ONE;
  Total=mean(of Rev:);
run;
proc print;
run;

/**
 *
 */
* No.
* Page