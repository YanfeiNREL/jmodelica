 /*
    Copyright (C) 2016 Modelon AB

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3 as published
    by the Free Software Foundation, or optionally, under the terms of the
    Common Public License version 1.0 as published by IBM.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License, or the Common Public License, for more details.

    You should have received copies of the GNU General Public License
    and the Common Public License along with this program.  If not,
    see <http://www.gnu.org/licenses/> or
    <http://www.ibm.com/developerworks/library/os-cpl.html/> respectively.
*/


/** \file jmi_math.h
 *  \brief Mathematical functions used in the run-time and code-gen.
 */

#ifndef _JMI_MATH_H
#define _JMI_MATH_H

#include "jmi_types.h"

/* Define the machine epsilon */
#define JMI_EPS 2.2204460492503131e-16
#define JMI_ALMOST_EPS (JMI_EPS*100)
#define JMI_INF   1e20                    /**< \brief A Very Large Number denoting infinity.*/
#define JMI_PI    3.14159265358979323846  /**< \brief The constant pi. */

/*#define ALMOST_ZERO(op) (jmi_abs(op)<=1e-6? JMI_TRUE: JMI_FALSE)*/
#define ALMOST_ZERO(op) LOG_EXP_AND(ALMOST_LT_ZERO(op),ALMOST_GT_ZERO(op))
#define ALMOST_LT_ZERO(op) (op<=JMI_ALMOST_EPS? JMI_TRUE: JMI_FALSE)
#define ALMOST_GT_ZERO(op) (op>=-JMI_ALMOST_EPS? JMI_TRUE: JMI_FALSE)
#define SURELY_LT_ZERO(op) (op<-JMI_ALMOST_EPS? JMI_TRUE: JMI_FALSE)
#define SURELY_GT_ZERO(op) (op>JMI_ALMOST_EPS? JMI_TRUE: JMI_FALSE)

/* Helper function for logging warnings from the "_equation"- and "_function"-functions */
void jmi_log_func_or_eq(jmi_t *jmi, const char cathegory_name[], const char func_name[], const char msg[], const char val[]);

/* Macros used together with the domain check option */
#ifdef MATHEMATICAL_DOMAIN_CHECKS
    #define MATHEMATICAL_DOMAIN_CHECKS_MSG "Using mathematical functions with domain checks."
    #define JMI_ABS_EQUATION(x)   jmi_abs(x)
    #define JMI_MAX_EQUATION(x,y) jmi_max(x,y)
    #define JMI_MIN_EQUATION(x,y) jmi_min(x,y)
    #define JMI_SIGN_EQUATION(x)  jmi_sign(x)
    #define JMI_DIVIDE_FUNCTION(name, num, den, msg) jmi_divide_function(name, num, den, msg)
    #define JMI_DIVIDE_EQUATION(jmi, num, den, msg)  jmi_divide_equation(jmi,  num, den, msg)
    #define JMI_EXP_EQUATION(jmi, x, msg)            jmi_exp_equation(jmi, x, msg)      
    #define JMI_EXP_FUNCTION(name, x, msg)           jmi_exp_function(name, x, msg)     
    #define JMI_TAN_EQUATION(jmi, x, msg)            jmi_tan_equation(jmi, x, msg)      
    #define JMI_TAN_FUNCTION(name, x, msg)           jmi_tan_function(name, x, msg)     
    #define JMI_ATAN_EQUATION(jmi, x, msg)           jmi_atan_equation(jmi, x, msg)     
    #define JMI_ATAN_FUNCTION(name, x, msg)          jmi_atan_function(name, x, msg)    
    #define JMI_TANH_EQUATION(jmi, x, msg)           jmi_tanh_equation(jmi, x, msg)     
    #define JMI_TANH_FUNCTION(name, x, msg)          jmi_tanh_function(name, x, msg)    
    #define JMI_COS_EQUATION(jmi, x, msg)            jmi_cos_equation(jmi, x, msg)      
    #define JMI_COS_FUNCTION(name, x, msg)           jmi_cos_function(name, x, msg)     
    #define JMI_ACOS_EQUATION(jmi, x, msg)           jmi_acos_equation(jmi, x, msg)     
    #define JMI_ACOS_FUNCTION(name, x, msg)          jmi_acos_function(name, x, msg)    
    #define JMI_COSH_EQUATION(jmi, x, msg)           jmi_cosh_equation(jmi, x, msg)     
    #define JMI_COSH_FUNCTION(name, x, msg)          jmi_cosh_function(name, x, msg)    
    #define JMI_SIN_EQUATION(jmi, x, msg)            jmi_sin_equation(jmi, x, msg)      
    #define JMI_SIN_FUNCTION(name, x, msg)           jmi_sin_function(name, x, msg)     
    #define JMI_ASIN_EQUATION(jmi, x, msg)           jmi_asin_equation(jmi, x, msg)     
    #define JMI_ASIN_FUNCTION(name, x, msg)          jmi_asin_function(name, x, msg)    
    #define JMI_SINH_EQUATION(jmi, x, msg)           jmi_sinh_equation(jmi, x, msg)     
    #define JMI_SINH_FUNCTION(name, x, msg)          jmi_sinh_function(name, x, msg)    
    #define JMI_SQRT_EQUATION(jmi, x, msg)           jmi_sqrt_equation(jmi, x, msg)     
    #define JMI_SQRT_FUNCTION(name, x, msg)          jmi_sqrt_function(name, x, msg)    
    #define JMI_LOG_EQUATION(jmi, x, msg)            jmi_log_equation(jmi, x, msg)      
    #define JMI_LOG_FUNCTION(name, x, msg)           jmi_log_function(name, x, msg)     
    #define JMI_LOG10_EQUATION(jmi, x, msg)          jmi_log10_equation(jmi, x, msg)    
    #define JMI_LOG10_FUNCTION(name, x, msg)         jmi_log10_function(name, x, msg)   
    #define JMI_ATAN2_EQUATION(jmi, x, y, msg)       jmi_atan2_equation(jmi, x, y, msg) 
    #define JMI_ATAN2_FUNCTION(name, x, y, msg)      jmi_atan2_function(name, x, y, msg)
    #define JMI_POW_EQUATION(jmi, x, y, msg)         jmi_pow_equation(jmi, x, y, msg)   
    #define JMI_POW_FUNCTION(name, x, y, msg)        jmi_pow_function(name, x, y, msg) 
#else
    #define MATHEMATICAL_DOMAIN_CHECKS_MSG "Using mathematical functions without any domain checks, caution is advised."
    #define JMI_ABS_EQUATION(x)   JMI_ABS(x)
    #define JMI_MAX_EQUATION(x,y) JMI_MAX(x,y)
    #define JMI_MIN_EQUATION(x,y) JMI_MIN(x,y)
    #define JMI_SIGN_EQUATION(x)  JMI_SIGN(x)
    #define JMI_DIVIDE_FUNCTION(name, num, den, msg) ((jmi_real_t)(num)/(jmi_real_t)(den))
    #define JMI_DIVIDE_EQUATION(jmi, num, den, msg)  ((jmi_real_t)(num)/(jmi_real_t)(den))
    #define JMI_EXP_EQUATION(jmi, x, msg)            (exp((jmi_real_t)(x)))
    #define JMI_EXP_FUNCTION(name, x, msg)           (exp((jmi_real_t)(x)))
    #define JMI_TAN_EQUATION(jmi, x, msg)            (tan((jmi_real_t)(x)))
    #define JMI_TAN_FUNCTION(name, x, msg)           (tan((jmi_real_t)(x)))
    #define JMI_ATAN_EQUATION(jmi, x, msg)           (atan((jmi_real_t)(x)))
    #define JMI_ATAN_FUNCTION(name, x, msg)          (atan((jmi_real_t)(x)))
    #define JMI_TANH_EQUATION(jmi, x, msg)           (tanh((jmi_real_t)(x)))
    #define JMI_TANH_FUNCTION(name, x, msg)          (tanh((jmi_real_t)(x)))
    #define JMI_COS_EQUATION(jmi, x, msg)            (cos((jmi_real_t)(x)))
    #define JMI_COS_FUNCTION(name, x, msg)           (cos((jmi_real_t)(x)))
    #define JMI_ACOS_EQUATION(jmi, x, msg)           (acos((jmi_real_t)(x)))
    #define JMI_ACOS_FUNCTION(name, x, msg)          (acos((jmi_real_t)(x)))
    #define JMI_COSH_EQUATION(jmi, x, msg)           (cosh((jmi_real_t)(x)))
    #define JMI_COSH_FUNCTION(name, x, msg)          (cosh((jmi_real_t)(x)))
    #define JMI_SIN_EQUATION(jmi, x, msg)            (sin((jmi_real_t)(x)))
    #define JMI_SIN_FUNCTION(name, x, msg)           (sin((jmi_real_t)(x)))
    #define JMI_ASIN_EQUATION(jmi, x, msg)           (asin((jmi_real_t)(x)))
    #define JMI_ASIN_FUNCTION(name, x, msg)          (asin((jmi_real_t)(x)))
    #define JMI_SINH_EQUATION(jmi, x, msg)           (sinh((jmi_real_t)(x)))
    #define JMI_SINH_FUNCTION(name, x, msg)          (sinh((jmi_real_t)(x)))
    #define JMI_SQRT_EQUATION(jmi, x, msg)           (sqrt((jmi_real_t)(x)))
    #define JMI_SQRT_FUNCTION(name, x, msg)          (sqrt((jmi_real_t)(x)))
    #define JMI_LOG_EQUATION(jmi, x, msg)            (log((jmi_real_t)(x)))
    #define JMI_LOG_FUNCTION(name, x, msg)           (log((jmi_real_t)(x)))
    #define JMI_LOG10_EQUATION(jmi, x, msg)          (log10((jmi_real_t)(x)))
    #define JMI_LOG10_FUNCTION(name, x, msg)         (log10((jmi_real_t)(x)))
    #define JMI_ATAN2_EQUATION(jmi, x, y, msg)       (atan2((jmi_real_t)(x), (jmi_real_t)(y)))
    #define JMI_ATAN2_FUNCTION(name, x, y, msg)      (atan2((jmi_real_t)(x), (jmi_real_t)(y)))
    #define JMI_POW_EQUATION(jmi, x, y, msg)         (pow((jmi_real_t)(x), (jmi_real_t)(y)))
    #define JMI_POW_FUNCTION(name, x, y, msg)        (pow((jmi_real_t)(x), (jmi_real_t)(y))) 
#endif

jmi_real_t jmi_pow(jmi_t *jmi, const char func_name[], jmi_real_t x, jmi_real_t y, const char msg[]);

/**
 * Function for checking if a vector contains NAN values. Returns the
 * index of the NAN (if found) in the parameter index_of_nan
 */
int jmi_check_nan(jmi_t *jmi, jmi_real_t* val, size_t n_val, jmi_int_t* index_of_nan);

jmi_real_t jmi_divide(jmi_t *jmi, const char func_name[], jmi_real_t num, jmi_real_t den, const char msg[]);

/**
 * Function to wrap division and report errors to the log, for use in functions.
 */
jmi_real_t jmi_divide_function(const char* name, jmi_real_t num, jmi_real_t den, const char* msg);

/**
 * Function to wrap division and report errors to the log, for use in equations.
 */
jmi_real_t jmi_divide_equation(jmi_t *jmi, jmi_real_t num, jmi_real_t den, const char* msg);


jmi_real_t jmi_sqrt(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C sqrt function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_sqrt_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C sqrt function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_sqrt_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_asin(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C asin function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_asin_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C asin function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_asin_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_acos(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C acos function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_acos_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C acos function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_acos_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_atan2(jmi_t *jmi, const char func_name[], jmi_real_t x, jmi_real_t y, const char msg[]);

/**
 * Function to wrap atan2 and report errors to the log, for use in functions.
 */
jmi_real_t jmi_atan2_function(const char* name, jmi_real_t x, jmi_real_t y, const char* msg);

/**
 * Function to wrap atan2 and report errors to the log, for use in equations.
 */
jmi_real_t jmi_atan2_equation(jmi_t *jmi, jmi_real_t x, jmi_real_t y, const char* msg);

jmi_real_t jmi_pow(jmi_t *jmi, const char func_name[], jmi_real_t x, jmi_real_t y, const char msg[]);

/**
 * Function to wrap the C pow function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_pow_function(const char* name, jmi_real_t x, jmi_real_t y, const char* msg);

/**
 * Function to wrap the C pow function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_pow_equation(jmi_t *jmi, jmi_real_t x, jmi_real_t y, const char* msg);


jmi_real_t jmi_exp(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C exp function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_exp_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C exp function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_exp_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_log(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C log function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_log_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C log function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_log_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_log10(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C log10 function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_log10_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C log10 function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_log10_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_sinh(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C sinh function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_sinh_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C sinh function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_sinh_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_cosh(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C cosh function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_cosh_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C cosh function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_cosh_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_tan(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C tan function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_tan_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C tan function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_tan_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_sin(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C sin function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_sin_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C sin function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_sin_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_cos(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C cos function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_cos_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C cos function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_cos_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_atan(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C atan function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_atan_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C atan function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_atan_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

jmi_real_t jmi_tanh(jmi_t *jmi, const char func_name[], jmi_real_t x, const char msg[]);

/**
 * Function to wrap the C tanh function and report errors to the log, for use in functions.
 */
jmi_real_t jmi_tanh_function(const char* name, jmi_real_t x, const char* msg);

/**
 * Function to wrap the C tanh function and report errors to the log, for use in equations.
 */
jmi_real_t jmi_tanh_equation(jmi_t *jmi, jmi_real_t x, const char* msg);

/**
 * Function to get the absolute value.
 * Is a separate function to avoid evaluating expressions several times.
 */
jmi_real_t jmi_abs(jmi_real_t v);

/**
 * Function to get the absolute value.
 * Is a separate function to avoid evaluating expressions several times.
 */
jmi_real_t jmi_sign(jmi_real_t v);

/**
 * Function to get the smaller of two values.
 * Is a separate function to avoid evaluating expressions twice.
 */
jmi_real_t jmi_min(jmi_real_t x, jmi_real_t y);

/**
 * Function to get the larger of two values.
 * Is a separate function to avoid evaluating expressions twice.
 */
jmi_real_t jmi_max(jmi_real_t x, jmi_real_t y);

/**
 * The round function for double numbers. 
 *
 */
jmi_real_t jmi_dround(jmi_real_t x);

/**
 * The remainder function for double numbers. 
 *
 */
jmi_real_t jmi_dremainder(jmi_t* jmi, jmi_real_t x, jmi_real_t y);

/**
 * The sample operator. Returns true if time = offset + i*h, i>=0 during
 * handling of an event. During continuous integration, false is returned.
 *
 */
jmi_real_t jmi_sample(jmi_t* jmi, jmi_real_t offset, jmi_real_t h);

#endif /* _JMI_MATH_H */
