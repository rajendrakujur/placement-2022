/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parse.y" /* yacc.c:339  */

#include <bits/stdc++.h>

using namespace std;

#define stmt_type 1
#define var_type 0
#define int_type 2
#define u_int_type 3
#define bool_type 4
#define numeric_constant 5
#define bool_type_exp 6
#define arith_type_exp 7

int yyparse(void);
int yylex(void); 
void yyerror(const char*);

string merge_code(vector<string>);
//vector<data> get_top_n(int);
vector<string> get_label(int);
vector<string> get_temp(int);
string to_string_(int);

int lable_count = 0;
int temp_var_count = 0;
map<string,string> vars;

struct true_false
{
	string true_lable;
	string false_lable;
};

struct data
{
	string code;
	string val;
	string id;
	string type;
	int width;
	int type2;
	int type3;
	int exp_type;
	string place;
	true_false jumps;
	data(){}
	data(string val) { this->val = val;}
};

struct symbol_talbe_row
{
	string type;
	string val;
	int type_id;
};

map<string,symbol_talbe_row> symbol_table;

stack<data> trace;
stack<data> special_stack1;
stack<data> special_stack2;

bool search(string var_name)
{
	if(symbol_table[var_name].type == "" || symbol_table[var_name].type == " " )
		return false;
	return true;
}

vector<data> get_top_n(int n)
{
	vector<data> top_n(n);
	for(int i=0;i<n;i++)
	{
		top_n[n-i-1] = trace.top();
		trace.pop();
	}
	return top_n;
}

void operator_code_generator(string oper)
{
	vector<data> obj = get_top_n(2);
	vector<string> temps = get_temp(1);
	vector<string> code_parts;
	//cout<<"\n"<<oper<<" : "<<obj[0].exp_type<<" "<<obj[1].exp_type<<endl;
	if(obj[0].exp_type == bool_type_exp || obj[1].exp_type == bool_type_exp )
	{
		cout<<"\nErro operator "+oper+" on [boolean] not permitted\n";
		exit(0);
	}

	data obj1;
	obj1.place = temps[0];
	code_parts.push_back(obj[0].code);
	code_parts.push_back(obj[1].code);
	code_parts.push_back(temps[0] + " := " + obj[0].place + " "+ oper + " " + obj[1].place);
	obj1.code = merge_code(code_parts);
	obj1.type2 = stmt_type;
	obj1.exp_type = arith_type_exp;
	trace.push(obj1);
}

void and_code_generator()
{
	vector<data> obj = get_top_n(2);
	vector<string> lables = get_label(1);
	vector<string> code_parts;

	code_parts.push_back(obj[0].code);
	code_parts.push_back(obj[0].jumps.true_lable+":");
	code_parts.push_back(obj[1].code);
	code_parts.push_back(obj[0].jumps.false_lable+":");
	code_parts.push_back(obj[1].jumps.false_lable+":");
	code_parts.push_back("goto "+lables[0]);

	data obj1;
	obj1.code = merge_code(code_parts);
	obj1.type2 = stmt_type;
	obj1.jumps.true_lable = obj[1].jumps.true_lable;
	obj1.jumps.false_lable = lables[0];
	obj1.exp_type = bool_type_exp;
	trace.push(obj1);

}

void or_code_generator()
{
	vector<data> obj = get_top_n(2);
	vector<string> lables = get_label(1);
	vector<string> code_parts;

	code_parts.push_back(obj[0].code);
	code_parts.push_back(obj[0].jumps.false_lable+":");
	code_parts.push_back(obj[1].code);
	code_parts.push_back(obj[0].jumps.true_lable+":");
	code_parts.push_back(obj[1].jumps.true_lable+":");
	code_parts.push_back("goto "+lables[0]);

	data obj1;
	obj1.code = merge_code(code_parts);
	obj1.type2 = stmt_type;
	obj1.jumps.true_lable = lables[0];
	obj1.jumps.false_lable = obj[1].jumps.false_lable;
	obj1.exp_type = bool_type_exp;
	trace.push(obj1);	
}

void rel_operator_code_generator(string oper)
{
	vector<data> obj = get_top_n(2);
	vector<string> code_parts;
	vector<string> lables = get_label(2);

	if( oper != "==" && oper != "!=")
	{
		if(obj[0].exp_type == bool_type_exp || obj[1].exp_type == bool_type_exp)
		{
			cout<<"\nErro operator "+oper+" on [boolean] not permitted\n";
			exit(0);
		}
	}
	//cout<<"\n"<<oper<<" : "<<obj[0].exp_type<<" "<<obj[1].exp_type<<endl;
	if(oper == "==" || oper == "!=")
	{
		if(obj[0].exp_type == bool_type_exp && obj[1].exp_type != bool_type_exp)
		{
			cout<<"\nErro operator "+oper+" on [boolean] vs [other] not permitted. Both should be boolean.\n";
			exit(0);
		}
		else if(obj[0].exp_type != bool_type_exp && obj[1].exp_type == bool_type_exp)
		{
			cout<<"\nErro operator "+oper+" on [boolean] vs [other] not permitted. both should be boolean;\n";
			exit(0);
		}
	}

	if(obj[0].type2 != var_type)
			code_parts.push_back(obj[0].code);
	if(obj[1].type2 != var_type)
			code_parts.push_back(obj[1].code);

	code_parts.push_back("if "+obj[0].place + " " + oper + " " + obj[1].place + " goto " + lables[0]);
	code_parts.push_back("goto "+lables[1]);
	data obj1;
	obj1.code = merge_code(code_parts);
	obj1.type2 = stmt_type;
	obj1.jumps.true_lable = lables[0];
	obj1.jumps.false_lable = lables[1];
	obj1.exp_type = bool_type_exp;
	trace.push(obj1);
}


#line 262 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


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
    loop_while = 258,
    keyword_if = 259,
    keyword_else = 260,
    tok_int = 261,
    tok_u_int = 262,
    tok_bool = 263,
    tok_switch_stmt = 264,
    tok_case = 265,
    tok_default = 266,
    tok_colon = 267,
    tok_break = 268,
    var = 269,
    tok_num = 270,
    binary_oper_per1 = 271,
    binary_oper_per2 = 272,
    bool_init = 273,
    tok_l_or = 274,
    tok_l_and = 275,
    tok_b_or = 276,
    tok_b_xor = 277,
    tok_b_and = 278,
    tok_equal_to = 279,
    tok_not_equal_to = 280,
    tok_less_than = 281,
    tok_less_eql = 282,
    tok_greater_than = 283,
    tok_greater_eql = 284,
    tok_plus = 285,
    tok_minus = 286,
    tok_mul = 287,
    tok_div = 288,
    tok_mod = 289,
    tok_b_not = 290,
    tok_l_not = 291,
    IFX = 292
  };
#endif
/* Tokens.  */
#define loop_while 258
#define keyword_if 259
#define keyword_else 260
#define tok_int 261
#define tok_u_int 262
#define tok_bool 263
#define tok_switch_stmt 264
#define tok_case 265
#define tok_default 266
#define tok_colon 267
#define tok_break 268
#define var 269
#define tok_num 270
#define binary_oper_per1 271
#define binary_oper_per2 272
#define bool_init 273
#define tok_l_or 274
#define tok_l_and 275
#define tok_b_or 276
#define tok_b_xor 277
#define tok_b_and 278
#define tok_equal_to 279
#define tok_not_equal_to 280
#define tok_less_than 281
#define tok_less_eql 282
#define tok_greater_than 283
#define tok_greater_eql 284
#define tok_plus 285
#define tok_minus 286
#define tok_mul 287
#define tok_div 288
#define tok_mod 289
#define tok_b_not 290
#define tok_l_not 291
#define IFX 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 198 "parse.y" /* yacc.c:355  */

	char *val;

#line 377 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 394 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  32
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   394

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  101

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      40,    41,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    38,
       2,    39,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   222,   222,   227,   228,   237,   238,   239,   240,   241,
     242,   271,   302,   304,   307,   315,   336,   364,   381,   404,
     429,   437,   445,   455,   456,   460,   461,   462,   463,   464,
     465,   467,   468,   469,   470,   471,   472,   474,   475,   476,
     477,   478,   480,   504,   524,   539,   542,   563,   573
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "loop_while", "keyword_if",
  "keyword_else", "tok_int", "tok_u_int", "tok_bool", "tok_switch_stmt",
  "tok_case", "tok_default", "tok_colon", "tok_break", "var", "tok_num",
  "binary_oper_per1", "binary_oper_per2", "bool_init", "tok_l_or",
  "tok_l_and", "tok_b_or", "tok_b_xor", "tok_b_and", "tok_equal_to",
  "tok_not_equal_to", "tok_less_than", "tok_less_eql", "tok_greater_than",
  "tok_greater_eql", "tok_plus", "tok_minus", "tok_mul", "tok_div",
  "tok_mod", "tok_b_not", "tok_l_not", "IFX", "';'", "'='", "'('", "')'",
  "'{'", "'}'", "$accept", "start_", "stmts", "stmt", "switch_stmt",
  "switch_block", "case_stmt", "while_loop", "if_stmt", "decl",
  "data_type", "block", "expr", "variable", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    59,    61,
      40,    41,   123,   125
};
# endif

#define YYPACT_NINF -76

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-76)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     160,   -33,   -29,   -76,   -76,   -76,   -26,   -76,   -76,   -76,
      35,    35,    35,    35,    20,   160,   -76,   -76,   -76,   -76,
     -76,    -5,   274,   -13,    35,    35,    35,   -76,   -76,   -76,
     -76,   182,   -76,   -76,     8,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      35,   -76,    35,   205,   228,   251,   -76,   -76,    -5,   313,
     327,   340,   156,   351,   360,   360,   119,   119,   119,   119,
      -9,    -9,   -76,   -76,   -76,   294,   106,   106,     1,    10,
     -76,   160,   -76,   -76,    46,    42,   -76,    87,   106,    -5,
       2,   -76,   -76,   -76,    43,   -76,   -76,   160,   125,    16,
     -76
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    20,    21,    22,     0,    46,    47,    48,
       0,     0,     0,     0,     0,     2,     3,     6,     7,     8,
       5,     0,     0,    45,     0,     0,     0,    44,    45,    43,
      42,     0,     1,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,     0,     0,     0,     0,    25,    18,     0,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,     0,     0,     0,     0,     0,
      10,     0,    24,    15,    17,     0,    19,     0,     0,     0,
       0,    12,    23,    16,     0,    11,    13,     0,     0,     0,
      14
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -76,   -76,   -75,   -14,   -76,   -76,   -34,   -76,   -76,   -76,
     -76,   -69,    -8,     0
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    14,    15,    16,    17,    90,    91,    18,    19,    20,
      21,    83,    22,    28
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      23,    33,    27,    29,    30,    31,    87,    24,    84,     7,
       8,    25,    89,     9,    26,    23,    53,    54,    55,    93,
      32,    34,    98,    48,    49,    50,    52,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    85,    75,    95,    57,    58,    86,     7,
       8,    88,    89,     9,   100,    97,    96,     0,    79,     0,
       0,     0,    82,    82,     0,     0,    10,     0,     0,     0,
      11,    12,     0,    33,    82,    13,    23,    23,     0,     0,
       0,    23,     0,     0,    33,     0,     0,    23,    23,    94,
       1,     2,     0,     3,     4,     5,     6,    23,    23,     0,
       0,     7,     8,     0,     0,     9,     0,     0,     0,     1,
       2,     0,     3,     4,     5,     6,     0,     0,    10,     0,
       7,     8,    11,    12,     9,     0,     0,    13,     1,     2,
      92,     3,     4,     5,     6,     0,     0,    10,    99,     7,
       8,    11,    12,     9,     0,     0,    13,     0,    81,    46,
      47,    48,    49,    50,     0,     0,    10,     0,     0,     0,
      11,    12,     0,     1,     2,    13,     3,     4,     5,     6,
       0,     0,     0,     0,     7,     8,     0,     0,     9,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    10,     0,     0,     0,    11,    12,     0,     0,     0,
      13,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,     0,     0,     0,
       0,     0,     0,    56,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
       0,     0,     0,     0,     0,     0,    76,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,     0,     0,     0,     0,     0,     0,    77,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,     0,     0,     0,     0,
       0,     0,    78,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,     0,
       0,     0,    51,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,     0,
       0,     0,    80,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    42,    43,    44,    45,
      46,    47,    48,    49,    50
};

static const yytype_int8 yycheck[] =
{
       0,    15,    10,    11,    12,    13,    81,    40,    77,    14,
      15,    40,    10,    18,    40,    15,    24,    25,    26,    88,
       0,    21,    97,    32,    33,    34,    39,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    42,    52,    43,    38,    39,    38,    14,
      15,     5,    10,    18,    38,    12,    90,    -1,    58,    -1,
      -1,    -1,    76,    77,    -1,    -1,    31,    -1,    -1,    -1,
      35,    36,    -1,    87,    88,    40,    76,    77,    -1,    -1,
      -1,    81,    -1,    -1,    98,    -1,    -1,    87,    88,    89,
       3,     4,    -1,     6,     7,     8,     9,    97,    98,    -1,
      -1,    14,    15,    -1,    -1,    18,    -1,    -1,    -1,     3,
       4,    -1,     6,     7,     8,     9,    -1,    -1,    31,    -1,
      14,    15,    35,    36,    18,    -1,    -1,    40,     3,     4,
      43,     6,     7,     8,     9,    -1,    -1,    31,    13,    14,
      15,    35,    36,    18,    -1,    -1,    40,    -1,    42,    30,
      31,    32,    33,    34,    -1,    -1,    31,    -1,    -1,    -1,
      35,    36,    -1,     3,     4,    40,     6,     7,     8,     9,
      -1,    -1,    -1,    -1,    14,    15,    -1,    -1,    18,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    31,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,
      40,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    38,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    38,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    26,    27,    28,    29,
      30,    31,    32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     6,     7,     8,     9,    14,    15,    18,
      31,    35,    36,    40,    45,    46,    47,    48,    51,    52,
      53,    54,    56,    57,    40,    40,    40,    56,    57,    56,
      56,    56,     0,    47,    57,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    38,    39,    56,    56,    56,    41,    38,    39,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    41,    41,    41,    57,
      38,    42,    47,    55,    55,    42,    38,    46,     5,    10,
      49,    50,    43,    55,    57,    43,    50,    12,    46,    13,
      38
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    47,    47,    47,
      47,    48,    49,    49,    50,    51,    52,    52,    53,    53,
      54,    54,    54,    55,    55,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    57,    57,    57
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     2,
       4,     7,     1,     2,     6,     5,     7,     5,     3,     5,
       1,     1,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 222 "parse.y" /* yacc.c:1646  */
    {
					cout<<trace.top().code<<endl;
					trace.pop();
				  }
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 227 "parse.y" /* yacc.c:1646  */
    { /* no change */}
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 229 "parse.y" /* yacc.c:1646  */
    {
	 					vector<data> obj = get_top_n(2);
	 					data obj1;
	 					obj1.code = obj[0].code + obj[1].code;
	 					trace.push(obj1);
	 				}
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 237 "parse.y" /* yacc.c:1646  */
    { /* no change */}
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 238 "parse.y" /* yacc.c:1646  */
    {/* no change */}
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 239 "parse.y" /* yacc.c:1646  */
    { /* no change */}
#line 1636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 240 "parse.y" /* yacc.c:1646  */
    { /* no change */}
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 241 "parse.y" /* yacc.c:1646  */
    { /* no change */ }
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 243 "parse.y" /* yacc.c:1646  */
    {
								vector<data> obj = get_top_n(2);
								if( !search(obj[0].place))
								{
									cout<<"\nError "<<obj[0].place<<" is used without declaration\n";
									exit(0);
								}
							//	cout<<" types : "<<obj[0].exp_type<< " : "<<obj[1].exp_type<<endl;
								if(obj[0].exp_type != obj[1].exp_type)
								{
									cout<<"\nInvalid assignment\n";
									exit(0);
								}

								
								vector<string> code_parts;

								data obj1;
								obj1.place = string(obj[0].place);

								code_parts.push_back(obj[1].code);
								code_parts.push_back(obj1.place + " := " + obj[1].place);

								obj1.code = merge_code(code_parts);
								trace.push(obj1);
							}
#line 1679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 272 "parse.y" /* yacc.c:1646  */
    {
					vector<data> obj = get_top_n(1);
					vector<string> code_parts;
					vector<string> lables = get_label(special_stack1.size()+1);

					code_parts.push_back(obj[0].code);
					int i = 0;
					while(!special_stack1.empty())
					{
						code_parts.push_back("if "+ obj[0].place +" == " + special_stack1.top().place +" goto "+lables[i]);
						i++;
						special_stack1.pop();
					}
					code_parts.push_back("goto "+lables[lables.size()-1]);
					i = 0;
					while(!special_stack2.empty())
					{
						code_parts.push_back(lables[i]+":");
						code_parts.push_back(special_stack2.top().code);
						code_parts.push_back("goto "+lables[lables.size()-1]);
						special_stack2.pop();
						i++;
					}
					code_parts.push_back(lables[lables.size()-1]+":");
					data obj3;
					obj3.code = merge_code(code_parts);
					trace.push(obj3);
				}
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 302 "parse.y" /* yacc.c:1646  */
    {/* nothing */}
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 304 "parse.y" /* yacc.c:1646  */
    {/* nothing */}
#line 1724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 308 "parse.y" /* yacc.c:1646  */
    {
				vector<data> obj = get_top_n(2);
				special_stack1.push(obj[0]);
				special_stack2.push(obj[1]);
			}
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 316 "parse.y" /* yacc.c:1646  */
    {
											  	vector<data> obj = get_top_n(2);
											  	vector<string> lables = get_label(1);

											  	data obj3;
											  	vector<string> code_parts;
											  	code_parts.push_back(lables[0]+":");
											  	code_parts.push_back(obj[0].code);
											  	code_parts.push_back(obj[0].jumps.true_lable+":");
											  	//code_parts.push_back("if "+obj[0].place+" == 0 goto "+lables[1]);
											  	code_parts.push_back(obj[1].code);
											  	code_parts.push_back("goto "+ lables[0]);
											  	code_parts.push_back(obj[0].jumps.false_lable+":");

											  	obj3.code = merge_code(code_parts);

												trace.push(obj3);
											   }
#line 1757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 337 "parse.y" /* yacc.c:1646  */
    {
										vector<data> obj = get_top_n(3);
										vector<string> lables = get_label(1);
										vector<string> code_parts;

										code_parts.push_back(obj[0].code);
										//code_parts.push_back("if "+obj[0].place + " == 0 goto "+lables[0]);
										code_parts.push_back(obj[0].jumps.true_lable+":");
										code_parts.push_back(obj[1].code);
										code_parts.push_back("goto "+lables[0]);

										code_parts.push_back(obj[0].jumps.false_lable+":");
										code_parts.push_back(obj[2].code);

										code_parts.push_back(lables[0]+":");

										// code_parts.push_back("goto "+lables[1]);
										// code_parts.push_back(obj[1].code);
										// code_parts.push_back("goto "+lables[1]);
										// code_parts.push_back(lables[0]+":");
										// code_parts.push_back(obj[2].code);
										// code_parts.push_back(lables[1]+":");

										data obj4;
										obj4.code = merge_code(code_parts);
										trace.push(obj4);
									}
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 365 "parse.y" /* yacc.c:1646  */
    {
										vector<data> obj = get_top_n(2);
										//vector<string> lables = get_label(1);
										vector<string> code_parts;

										code_parts.push_back(obj[0].code);
										//code_parts.push_back("if "+obj[0].place+" == 0 goto "+lables[0]);
										code_parts.push_back(obj[0].jumps.true_lable+":");
										code_parts.push_back(obj[1].code);
										//code_parts.push_back(lables[0]+":");
										code_parts.push_back(obj[0].jumps.false_lable+":");
										data obj3;
										obj3.code = merge_code(code_parts);
										trace.push(obj3);
									}
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 381 "parse.y" /* yacc.c:1646  */
    {
							vector<data> obj = get_top_n(2);
							if(!search(obj[1].place))
							{
								symbol_talbe_row row;
								row.type = obj[0].type;
								row.val = "";
								row.type_id = obj[0].type2;
								symbol_table[obj[1].place] = row;

								string x = "declare "+obj[1].place+"["+obj[0].type+"]\n";
								data obj1;
								obj1.code = x;
								obj1.place = obj[1].place;
								trace.push(obj1);
							}
							else
							{
								cout<<"\nError Redeclartion of variable : "<<obj[1].place<<endl;
								exit(0);
							}
						 }
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 405 "parse.y" /* yacc.c:1646  */
    {
							vector<data> obj = get_top_n(3);
							if(!search(obj[1].place) && (search(obj[2].place) || obj[2].type3 == numeric_constant) )
							{
								symbol_talbe_row row;
								row.type = obj[0].type;
								row.val = obj[2].place;
								row.type_id = obj[0].type2;
								symbol_table[obj[1].place] = row;

								string x = "declare "+obj[1].place+"["+obj[0].type+"] = "+row.val+"\n";
								data obj1;
								obj1.code = x;
								obj1.place = obj[1].place;
								trace.push(obj1);
							}
							else
							{
								cout<<"\nError in declartion of variable : "<<obj[1].place<<endl;
								exit(0);
							}
						}
#line 1863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 430 "parse.y" /* yacc.c:1646  */
    {
						data obj;
						obj.type = "int";
						obj.type2 = int_type;
						obj.width = 4;
						trace.push(obj);
					}
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 438 "parse.y" /* yacc.c:1646  */
    {
						data obj;
						obj.type = "unsingned_int";
						obj.type2 = u_int_type;
						obj.width = 4;
						trace.push(obj);
					}
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 446 "parse.y" /* yacc.c:1646  */
    {
						data obj;
						obj.type = "bool";
						obj.type2 = bool_type;
						obj.width = 1;
						trace.push(obj);
					}
#line 1899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 455 "parse.y" /* yacc.c:1646  */
    { /* no change */ }
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 456 "parse.y" /* yacc.c:1646  */
    { /* no change */ }
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 460 "parse.y" /* yacc.c:1646  */
    { /* no change */}
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 461 "parse.y" /* yacc.c:1646  */
    {  or_code_generator(); }
#line 1923 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 462 "parse.y" /* yacc.c:1646  */
    {  and_code_generator(); }
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 463 "parse.y" /* yacc.c:1646  */
    {  operator_code_generator("|"); }
#line 1935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 464 "parse.y" /* yacc.c:1646  */
    {  operator_code_generator("^"); }
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 465 "parse.y" /* yacc.c:1646  */
    {  operator_code_generator("&"); }
#line 1947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 467 "parse.y" /* yacc.c:1646  */
    {  rel_operator_code_generator("=="); }
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 468 "parse.y" /* yacc.c:1646  */
    { rel_operator_code_generator("!="); }
#line 1959 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 469 "parse.y" /* yacc.c:1646  */
    {  rel_operator_code_generator("<"); }
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 470 "parse.y" /* yacc.c:1646  */
    {  rel_operator_code_generator("<="); }
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 471 "parse.y" /* yacc.c:1646  */
    {  rel_operator_code_generator(">"); }
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 472 "parse.y" /* yacc.c:1646  */
    {  rel_operator_code_generator(">="); }
#line 1983 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 474 "parse.y" /* yacc.c:1646  */
    {  operator_code_generator("+"); }
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 475 "parse.y" /* yacc.c:1646  */
    {  operator_code_generator("-"); }
#line 1995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 476 "parse.y" /* yacc.c:1646  */
    {  operator_code_generator("*"); }
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 477 "parse.y" /* yacc.c:1646  */
    {  operator_code_generator("/"); }
#line 2007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 478 "parse.y" /* yacc.c:1646  */
    {  operator_code_generator("%"); }
#line 2013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 481 "parse.y" /* yacc.c:1646  */
    {
			vector<data> obj = get_top_n(1);
			if(obj[0].exp_type == arith_type_exp)
			{
				cout<<"! on arithmetic not allowed\n";
				exit(0);
			}
			vector<string> temps = get_temp(1);
			vector<string> code_parts;

			data obj1;
			//obj1.place = temps[0];
			code_parts.push_back(obj[0].code);
			//code_parts.push_back(temps[0] + " := " + obj[0].place);
			obj1.jumps.true_lable = obj[0].jumps.false_lable;
			obj1.jumps.false_lable = obj[0].jumps.true_lable;

			//code_parts.push_back("goto "+ obj[0].jumps.false_lable);
			obj1.code = merge_code(code_parts);
			obj1.type2 = stmt_type;
			obj1.exp_type = bool_type_exp;
			trace.push(obj1);
		}
#line 2041 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 505 "parse.y" /* yacc.c:1646  */
    {
			vector<data> obj = get_top_n(1);
			if(obj[0].exp_type == bool_type_exp)
			{
				cout<<"\n~ on boolean not permitted\n";
				exit(0);
			}
			vector<string> temps = get_temp(1);
			vector<string> code_parts;

			data obj1;
			obj1.place = temps[0];
			code_parts.push_back(obj[0].code);
			code_parts.push_back(temps[0] + " := ~ " + obj[0].place);
			obj1.code = merge_code(code_parts);
			obj1.type2 = stmt_type;
			obj1.exp_type = bool_type_exp;
			trace.push(obj1);	
		}
#line 2065 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 525 "parse.y" /* yacc.c:1646  */
    {
			vector<data> obj = get_top_n(1);
			vector<string> temps = get_temp(1);
			vector<string> code_parts;

			data obj1;
			obj1.place = temps[0];
			code_parts.push_back(obj[0].code);
			code_parts.push_back(temps[0] + " := 0 - " + obj[0].place);
			obj1.code = merge_code(code_parts);
			obj1.type2 = stmt_type;
			obj1.exp_type = arith_type_exp;
			trace.push(obj1);
		}
#line 2084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 539 "parse.y" /* yacc.c:1646  */
    { /* no change */ }
#line 2090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 542 "parse.y" /* yacc.c:1646  */
    {
							data obj;
							obj.place = string((yyvsp[0].val));
							if(search(string((yyvsp[0].val))))
								switch(symbol_table[string((yyvsp[0].val))].type_id)
								{
									case int_type:
													obj.exp_type = arith_type_exp;
													break;
									case u_int_type:
													obj.exp_type = arith_type_exp;
													break;
									case bool_type:
													obj.exp_type = bool_type_exp;
													break;
								}
						//	obj.code = string($1);
							obj.type2 = var_type;
							trace.push(obj); 
						}
#line 2115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 564 "parse.y" /* yacc.c:1646  */
    {
							data obj;
							obj.place = string((yyvsp[0].val));
							obj.type2 = var_type;
							obj.type3 = numeric_constant;
							obj.exp_type = arith_type_exp;
						//	obj.code = string($1);
							trace.push(obj);
						}
#line 2129 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 574 "parse.y" /* yacc.c:1646  */
    {
							data obj;
							obj.place = string((yyvsp[0].val));
							obj.type2 = var_type;
							obj.type3 = numeric_constant;
							obj.exp_type = bool_type_exp;
						//	obj.code = string($1);
							trace.push(obj);
						}
#line 2143 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2147 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 586 "parse.y" /* yacc.c:1906  */


include "lex.yy.c"

int main()
{
	yyparse();
	return 0;
}

string merge_code(vector<string> codes)
{
	string merged_code = "";
	for(int i=0;i<codes.size();i++)
	{
		if(codes[i] != "" && codes[i] != " ")
			merged_code += codes[i] + "\n";
	}
	return merged_code;
}

vector<string> get_label(int count)
{
	vector<string> new_lables;
	for(int i=0;i<count;i++,lable_count++)
	{
		new_lables.push_back("L"+to_string_(lable_count));
	}
	return new_lables;
}
vector<string> get_temp(int count)
{
	vector<string> new_temp_vars;
	for(int i=0;i<count;i++,temp_var_count++)
	{
		new_temp_vars.push_back("t"+to_string_(temp_var_count));
	}
	return new_temp_vars;
}
string to_string_(int num)
{
	char temp[100];
	sprintf(temp,"%d",num);
	return string(temp);
}

