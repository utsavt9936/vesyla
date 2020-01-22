/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_HOME_HERENVARNO_PROJECTS_GITR_SILAGO_VESYLA_DEMO_VESYLA_SRC_VPARSER_VPARSER_TAB_HPP_INCLUDED
# define YY_YY_HOME_HERENVARNO_PROJECTS_GITR_SILAGO_VESYLA_DEMO_VESYLA_SRC_VPARSER_VPARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LEXERROR = 258,
    LINE = 259,
    LD = 260,
    RD = 261,
    FOR = 262,
    END = 263,
    IF = 264,
    ELSEIF = 265,
    ELSE = 266,
    GLOBAL = 267,
    WHILE = 268,
    FUNCTION = 269,
    RETURN = 270,
    PRAGMASTART = 271,
    PARALLEL = 272,
    STRUCTURAL = 273,
    DPU = 274,
    RFILE = 275,
    MEMORY = 276,
    CDPU = 277,
    EVENDIST = 278,
    FULLDIST = 279,
    CUSTOMDIST = 280,
    COMPRESS = 281,
    DPUMODE = 282,
    DPUOUT = 283,
    DPU_SATURATION = 284,
    DPU_DYNAMIC = 285,
    ADDRESS_REG = 286,
    VAR_INPUT = 287,
    VAR_OUTPUT = 288,
    RACCU_VAR = 289,
    ADDRESS_VAR = 290,
    TEMP_VAR = 291,
    MEM_ADDRESS = 292,
    CONSTROW = 293,
    CONSTCOL = 294,
    CONSTDIMENSION = 295,
    CONSTPARALLELISM = 296,
    RESOURCE_SHARING_BEGIN = 297,
    RESOURCE_SHARING_END = 298,
    TEXT = 299,
    IDENTIFIER = 300,
    INTEGER = 301,
    DOUBLE = 302,
    IMAGINARY = 303,
    AND = 304,
    OR = 305,
    LTHAN = 306,
    LTHANE = 307,
    GTHAN = 308,
    GTHANE = 309,
    EQUAL = 310,
    UNEQUAL = 311,
    xo = 312,
    MMUL = 313,
    EMUL = 314,
    MDIV = 315,
    EDIV = 316,
    MLEFTDIV = 317,
    ELEFTDIV = 318,
    EPOWER = 319,
    MPOWER = 320,
    NOT = 321,
    UNARYPLUS = 322,
    UNARYMINUS = 323,
    TRANSPOSE = 324,
    CTRANSPOSE = 325
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 120 "/home/herenvarno/Projects/gitr/SiLago/vesyla_demo/vesyla/src/VParser/vparser.y" /* yacc.c:1909  */

          char* text;
          char* symbol;

          int integerVal;
          double doubleVal;
          int imaginaryVal;


          int ParallelModeType;
          int StorageTypeE;
          int PragmaConstantTypeE;
          int RaccuOptionsType;
          int StorageDistributionType;
          int VariableTypeE;


          class Array * ArrayType;
          class DPUPragma * DPUPragmaType;
          class Expression * ExpressionType;
          class FunctionDeclaration * FunctionDeclarationType;
          class Identifier * IdentifierType;
          class Name * NameType;
          class Pragma * PragmaType;
          class RangeExpression * RangeExpressionType;
          class Statement * StatementType;

          struct ArrayLinker * ArrayLinkerType;
          struct ExpressionLinker * ExpressionLinkerType;
          struct StatementLinker * StatementLinkerType;
          struct NameLinker * NameLinkerType;
          struct DPUOptions * DPUOptionsType;
          struct StorageOptions * StorageOptionsType;

          struct _variable {
            int size;
            char** entries;
          } variables;

          int delimiter;

          struct _var_expr_t* vexpression;

          struct _singleton {
            int size;
            struct _expr_t** expressions;
          } singletons;

          struct _global_t* globalStatement;
          struct _while_t* whileStatement;
        

#line 178 "/home/herenvarno/Projects/gitr/SiLago/vesyla_demo/vesyla/src/VParser/vparser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_HOME_HERENVARNO_PROJECTS_GITR_SILAGO_VESYLA_DEMO_VESYLA_SRC_VPARSER_VPARSER_TAB_HPP_INCLUDED  */
