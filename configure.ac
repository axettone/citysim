AC_INIT([CitySim], 1.0)
AM_INIT_AUTOMAKE([-Wall])
AC_PROG_CC
AC_CHECK_LIB([m],[cos],[],
    [
        AC_MSG_ERROR([Could not find MATH library])
    ])
AC_CHECK_LIB([gslcblas],[cblas_dgemm],[],
[
    AC_MSG_ERROR([Could not find GSLCBLAS library])
])
AC_CHECK_LIB([gsl],[gsl_blas_dgemm],[],
[
    AC_MSG_ERROR([Could not find GSL library])
])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile])
AC_OUTPUT
