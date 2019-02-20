%{

/*
 *  Lexical specification for MATLAB 
 *  Command-line options: -f
 */

//! Yu Yang 2017-08-01
// After move bison/flex generation to CMAKE, the header file name changes
// CHANGE BEGIN
#include "vparser.tab.hpp"
// CHANGE END

#include "FlexUtility.hpp"
#include <ctype.h>


#define Return(value, token)  \
{                             \
  printLexToken(value);       \
  return token;               \
}

int gBracketDepth;

void yyinsert_comma_in_input(const int);

%}

%option noyywrap
%s TRANSPOSE_STATE
%x PRAGMA_STATE

HSPACE             [ \t]
HSPACES            {HSPACE}+
NEWLINE            \n|\r|\f
NEWLINES           {NEWLINE}+

ELLIPSIS           \.\.\.
CONTINUATION       {ELLIPSIS}[^\n\r\f]*{NEWLINE}?

COMMENT            \%[^\!][^\n\r\f]*{NEWLINE}?

IDENTIFIER         [_a-zA-Z][_a-zA-Z0-9]*
DIGIT              [0-9]
INTEGER            {DIGIT}+
EXPONENT           [DdEe][+-]?{DIGIT}+
MANTISSA           ({DIGIT}+\.)|({DIGIT}*\.{DIGIT}+)
FLOATINGPOINT      {MANTISSA}{EXPONENT}?
DOUBLE             ({INTEGER}{EXPONENT})|{FLOATINGPOINT}
NUMBER             {INTEGER}|{DOUBLE}
IMAGINARYUNIT      [ij]


%%


"for"                           {
                                  Return("FOR", FOR);
                                }


"end"                           {
                                  Return("END", END);
                                }


"if"                            {
                                  Return("IF", IF);
                                }


"elseif"                        {
                                  Return("ELSEIF", ELSEIF);
                                }


"else"                          {
                                  Return("ELSE", ELSE);
                                }


"global"                        {
                                  Return("GLOBAL", GLOBAL);
                                }


"while"                         {
                                  Return("WHILE", WHILE);
                                }


"function"                      {
                                  Return("FUNCTION", FUNCTION);
                                }


"return"                        {
                                  Return("RETURN", RETURN);
                                }


<INITIAL>'[^'\n\r\f]*'/'        {
                                  yymore();
                                }


,                               {
                                  BEGIN(INITIAL);
                                  Return("','", ',');
                                }


;                               {
                                  BEGIN(INITIAL);
                                  Return("';'", ';');
                                }


<INITIAL>'[^'\r\f\n]*'          {
                                  // TODO: THIS PART HAS BEEN MODIFIED

                                  int i, size;
                                  char* modified;
                                  const int length = yyleng-2;

                                  for (size = 0, i = 1; i <= length; size++, i++)
                                    if (*(yytext+i) == '\'')
                                      i++;

                                  modified = new char [size + 1];
                                  *(modified+size) = '\0';

                                  for (size = 0, i = 1; i <= length; size++, i++)
                                  {
                                    *(modified+size) = *(yytext+i);

                                    if (*(yytext+i) == '\'')
                                      i++;
                                  }

                                  yylval.text = modified;

                                  Return("TEXT", TEXT);
                                }


{NUMBER}{IMAGINARYUNIT}         {
                                  BEGIN(TRANSPOSE_STATE);

                                  *(yytext+yyleng-1) = '\0';

                                  yylval.imaginaryVal = atoi(yytext);

                                  Return("IMAGINARY", IMAGINARY);
                                }


{DIGIT}+/\.[*/\\^]              {
                                  yylval.integerVal = atoi(yytext);

                                  Return("INTEGER", INTEGER);
                                }


{DIGIT}+/\.'                    {
                                  yylval.integerVal = atoi(yytext);
                                  Return("INTEGER", INTEGER);
                                }


{INTEGER}                       {
                                  BEGIN(TRANSPOSE_STATE);

                                  yylval.integerVal = atoi(yytext);
                                  yyinsert_comma_in_input(INTEGER);

                                  Return("INTEGER", INTEGER);
                                }


{DOUBLE}                        {
                                  BEGIN(TRANSPOSE_STATE);

                                  yylval.doubleVal = atof(yytext);

                                  Return("DOUBLE", DOUBLE);
                                }


{HSPACES}                       {
                                  BEGIN(INITIAL);
                                }

<PRAGMA_STATE>{HSPACES}         {
                                }


{CONTINUATION}                  {
                                  GlobalValues::gSourceLine++;
                                }


<*>{NEWLINES}                   {
                                  BEGIN(INITIAL);
                                  GlobalValues::gSourceLine += yyleng;
                                  Return("LINE", LINE);
                                }


{IDENTIFIER}                    {
                                  BEGIN(TRANSPOSE_STATE);

                                  yylval.symbol = new char [yyleng + 1];
                                  strncpy(yylval.symbol, yytext, yyleng + 1);

                                  yyinsert_comma_in_input(IDENTIFIER);

                                  Return("IDENTIFIER", IDENTIFIER);
                                }


{COMMENT}                       {
                                  BEGIN(INITIAL);
                                  GlobalValues::gSourceLine++;

                                  Return("LINE", LINE);
                                }


\%\!							{
                                  //cout<<"\nPragma detected!\n";

                                  BEGIN(PRAGMA_STATE);
                                  Return("PRAGMASTART", PRAGMASTART);
                                }
								
<PRAGMA_STATE>"parallel"        {
                                  Return("PARALLEL", PARALLEL);
                                }

<PRAGMA_STATE>"structural"      {
                                  Return("STRUCTURAL", STRUCTURAL);
                                }

<PRAGMA_STATE>"DPU"             {
                                  Return("DPU", DPU);
                                }

<PRAGMA_STATE>"CDPU"            {
                                  Return("CDPU", CDPU);
                                }

<PRAGMA_STATE>"RFILE"           {
                                  Return("RFILE", RFILE);
                                }

<PRAGMA_STATE>"MEM"             {
                                  Return("MEMORY", MEMORY);
                                }

<PRAGMA_STATE>"ADDRESS_VAR"     {
								  BEGIN(INITIAL);
                                  Return("ADDRESS_VAR", ADDRESS_VAR);
                                }

<PRAGMA_STATE>"RACCU_VAR"       {
								  //BEGIN(INITIAL);
                                  Return("RACCU_VAR", RACCU_VAR);
                                }

<PRAGMA_STATE>"TEMP_VAR"        {
								  BEGIN(INITIAL);
                                  Return("TEMP_VAR", TEMP_VAR);
                                }

<PRAGMA_STATE>"RESOURCE_SHARING_BEGIN" {
								  BEGIN(INITIAL);
                                  Return("RESOURCE_SHARING_BEGIN", RESOURCE_SHARING_BEGIN);
                                }

<PRAGMA_STATE>"RESOURCE_SHARING_END" {
								  BEGIN(INITIAL);
                                  Return("RESOURCE_SHARING_END", RESOURCE_SHARING_END);
                                }

<PRAGMA_STATE>{INTEGER}         {
                                  yylval.integerVal = atoi(yytext);
                                  yyinsert_comma_in_input(INTEGER);

                                  Return("INTEGER", INTEGER);
                                }

<PRAGMA_STATE>\<                {
                                  Return("'<'", '<');
                                }

<PRAGMA_STATE>\>                {
                                  //BEGIN(INITIAL);
                                  Return("'>'", '>');
                                }

<PRAGMA_STATE>\,                {
                                  Return("','", ',');
                                }

<PRAGMA_STATE>\=                {
                                  Return("'='", '=');
                                }

<PRAGMA_STATE>\[                {
								  BEGIN(INITIAL);
                                  Return("'['", '[');
                                }

<PRAGMA_STATE>\]                {
                                  Return("']'", ']');
                                }

<PRAGMA_STATE>"mod"             {
                                  Return("DPUMODE", DPUMODE);
                                }

<PRAGMA_STATE>"out"             {
                                  Return("DPUOUT", DPUOUT);
                                }

<PRAGMA_STATE>"sat"             {
                                  Return("DPU_SATURATION", DPU_SATURATION);
                                }

<PRAGMA_STATE>"address"			{
                                  Return("ADDRESS", ADDRESS_REG);
								}

<PRAGMA_STATE>"even_dist"       {
                                  Return("EVENDIST", EVENDIST);
                                }

<PRAGMA_STATE>"full_dist"       {
                                  Return("FULLDIST", FULLDIST);
                                }

<PRAGMA_STATE>"custom_dist"     {
                                  Return("CUSTOMDIST", CUSTOMDIST);
                                }

<PRAGMA_STATE>"input"	        {
                                  Return("VAR_INPUT", VAR_INPUT);
                                }

<PRAGMA_STATE>"output"	        {
                                  Return("VAR_OUTPUT", VAR_OUTPUT);
                                }

<PRAGMA_STATE>"<mem_address>"   {
								  BEGIN(INITIAL);
                                  Return("MEM_ADDRESS", MEM_ADDRESS);
                                }


<PRAGMA_STATE>"row"             {
                                  BEGIN(INITIAL);
                                  Return("CONSTROW", CONSTROW);
                                }


<PRAGMA_STATE>"col"             {
                                  BEGIN(INITIAL);
                                  Return("CONSTCOL", CONSTCOL);
                                }


<PRAGMA_STATE>"dimension"       {
                                  BEGIN(INITIAL);
                                  Return("CONSTDIMENSION", CONSTDIMENSION);
                                }


<PRAGMA_STATE>"parallelism"     {
                                  BEGIN(INITIAL);
                                  Return("CONSTPARALLELISM", CONSTPARALLELISM);
                                }
   

&                               {
                                  BEGIN(INITIAL);
                                  Return("AND", AND);
                                }


\|                              {
                                  BEGIN(INITIAL);
                                  Return("OR", OR);
                                }


\<                              {
                                  BEGIN(INITIAL);
                                  Return("LTHAN", LTHAN);
                                }


\<=                             {
                                  BEGIN(INITIAL);
                                  Return("LTHANE", LTHANE);
                                }


>                               {
                                  BEGIN(INITIAL);
                                  Return("GTHAN", GTHAN);
                                }


>=                              {
                                  BEGIN(INITIAL);
                                  Return("GTHANE", GTHANE);
                                }


==                              {
                                  BEGIN(INITIAL);
                                  Return("EQUAL", EQUAL);
                                }


~=                              {
                                  BEGIN(INITIAL);
                                  Return("UNEQUAL", UNEQUAL);
                                }


:                               {
                                  BEGIN(INITIAL);
                                  Return("':'", ':');
                                }


\+                              {
                                  BEGIN(INITIAL);
                                  Return("'+'", '+');
                                }


-                               {
                                  BEGIN(INITIAL);
                                  Return("'-'", '-');
                                }


\*                              {
                                  BEGIN(INITIAL);
                                  Return("MMUL", MMUL);
                                }


".*"                            {
                                  BEGIN(INITIAL);
                                  Return("EMUL", EMUL);
                                }


\/                              {
                                  BEGIN(INITIAL);
                                  Return("MDIV", MDIV);
                                }


"./"                            {
                                  BEGIN(INITIAL);
                                  Return("EDIV", EDIV);
                                }


\\                              {
                                  BEGIN(INITIAL);
                                  Return("MLEFTDIV", MLEFTDIV);
                                }


\.\\                            {
                                  BEGIN(INITIAL);
                                  Return("ELEFTDIV", ELEFTDIV);
                                }


{HSPACES}\.'                    {
                                  Return("LEXERROR", LEXERROR);
                                }


\.'                             {
                                  BEGIN(TRANSPOSE_STATE);
                                  Return("TRANSPOSE", TRANSPOSE);
                                }


\.^                             {
                                  BEGIN(INITIAL);
                                  Return("EPOWER", EPOWER);
                                }


\^                              {
                                  BEGIN(INITIAL);
                                  Return("MPOWER", MPOWER);
                                }


~                               {
                                  BEGIN(INITIAL);
                                  Return("NOT", NOT);
                                }


<TRANSPOSE_STATE>'              {
                                  Return("CTRANSPOSE", CTRANSPOSE);
                                }


<INITIAL>'                      {
                                  Return("LEXERROR", LEXERROR);
                                }


\[                              {
                                  if (gBracketDepth)
                                  {
                                    gBracketDepth++;
                                    Return("'['", '[');
                                  }

                                  int current = 0, next = 0;
                                  char* buffer = 0;
                                  int level = 1, length = 0;

                                  while (level && (current = yyinput()) != EOF)
                                  {
                                    buffer = realloc_string(buffer, ++length);

                                    *(buffer+length-1) = current;

                                    if (current == '[')
                                      level++;

                                    if (current == ']')
                                      level--;
                                  }

                                  if (level)
                                    Return("LEXERROR", LEXERROR);

                                  while ((current = yyinput()) != EOF)
                                  {
                                    buffer = realloc_string(buffer, ++length);

                                    *(buffer+length-1) = current;

                                    if (current != ' ' && current != '\t')
                                      break;
                                  }

                                  if ((next = yyinput()) != EOF)
                                  {
                                    buffer = realloc_string(buffer, ++length);

                                    *(buffer+length-1) = next;
                                  }

                                  for (; length > 0; length--)
                                    unput(*(buffer+length-1));

                                  free(buffer);

                                  gBracketDepth = 1;

                                  if (current == '=' && next != '=')
								                  {
                                    Return("LD", LD);
								                  }
                                  else
								                  {
                                    Return("'['", '[');
								                  }
                                }


\]/{HSPACE}*=[^=]               {
                                  BEGIN(INITIAL);
                                  gBracketDepth--;
                                  Return("RD", RD);
                                }


\]                              {
                                  BEGIN(TRANSPOSE_STATE);
                                  gBracketDepth--;
                                  Return("']'", ']');
                                }


\(                              {
                                  BEGIN(INITIAL);
                                  Return("'('", '(');
                                }


\)                              {
                                  BEGIN(TRANSPOSE_STATE);
                                  Return("')'", ')');
                                }


=                               {
                                  BEGIN(INITIAL);
                                  Return("'='", '=');
                                }


.                               {
                                  Return("LEXERROR", LEXERROR);
                                }


%%

void yyinsert_comma_in_input(const int lastToken) {

  int count, current, next;

  extern int gBracketDelimiter;

  printLexMessage("\nEntering<yyinsert_comma_in_input> ...\n");

  if (!(gBracketDelimiter == '[' || gBracketDelimiter == LD))
    return;

  for (count = 1; ; count++) 
  {
    current = yyinput();

    if (current != ' ' && current != '\t')
      break;
  }

  if (current == ','  || current == ';'  || current == ']'  ||
      current == '*'  || current == '^'  || current == ':'  ||
      current == '<'  || current == '>'  || current == '='  ||
      current == '&'  || current == '|'  || current == '/'  ||
      current == '\\' || current == '\n' || current == '\r' ||
      current == '\f' || current == '%'  || (current == '\'' && count == 1))
  {
    unput(current);
    return;
  }

  if (current == '(' && (gBracketDelimiter == LD || (lastToken == IDENTIFIER && count == 1)))
  {
    unput(current);
    return;
  }

  if (isalpha(current) && (lastToken == INTEGER || lastToken == DOUBLE) && count == 1)
  {
    unput(current);
    return;
  }

  next = yyinput();
  ++count;

  if (current == '.' &&
      (next == '\'' || next == '*' || next == '^' ||
       next == '/'  || next == '\\' || next == '.'))
  {
    unput(next);
    unput('.');

    if (next == '\'' && count > 2)
      unput(' ');

    return;
  }

  if (current == '~' && next == '=')
  {
    unput('=');
    unput('~');

    return;
  }

  if (current == '+' || current == '-')
    if (count == 2 || next == ' ' || next == '\t')
    {
      unput(next);
      unput(current);

      return;
    }

  unput(next);
  unput(current);
  unput(',');
}
