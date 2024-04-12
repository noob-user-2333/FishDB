%include{
#include "../Lexer.h"

}



%token_type {Lexer::Token *}

%token KW_NUM_INT KW_NUM_DOUBLE KW_LB KW_RB KW_COMMA KW_END KW_DOT KW_SPACE KW_MORE KW_MEQ .
%token KW_LESS KW_LEQ KW_EQUAL KW_PLUS KW_SUB KW_STAR KW_DIV KW_PERCENT KW_BITAND KW_BITOR .
%token KW_AND KW_OR KW_XOR KW_NOTEQUAL KW_BANG KW_LSHIFT KW_RSHIFT KW_STRING KW_ID .
%token  KW_ASC  KW_BY  KW_CHAR  KW_CREATE  KW_DELETE  KW_DESC  KW_DISTINCT  KW_DROP  KW_FLOAT  KW_FROM.
%token  KW_GROUP  KW_HAVING  KW_INDEX  KW_INSERT  KW_INT  KW_INTO  KW_JOIN  KW_LONG  KW_ON  KW_ORDER .
%token  KW_SELECT  KW_SET  KW_SHORT  KW_TABLE  KW_UPDATE  KW_VALUES  KW_VCHAR  KW_WHERE.


%left KW_PLUS KW_SUB.
%left KW_STAR KW_DIV.
%left KW_JOIN.
%left KW_EQUAL KW_NOTEQUAL KW_MORE KW_LESS KW_MEQ KW_LEQ.
%left KW_AND KW_OR.


//insert
sql ::= insert_statement KW_END .
insert_statement ::= KW_INSERT KW_INTO KW_ID KW_VALUES KW_LB value_list KW_RB.
value_list ::= value.
value_list ::= value_list KW_COMMA value.
value ::= KW_NUM_INT.
value ::= KW_NUM_DOUBLE.
value ::= KW_STRING.

//select
sql ::= select_statement KW_END.
select_statement ::= KW_SELECT  item_list KW_FROM KW_ID where_statement.
item_list ::= item.
item_list ::= item_list KW_COMMA item.
item ::= KW_STAR.
item ::= KW_ID.

where_statement ::= .
where_statement ::= KW_WHERE condition_list.

condition_list ::= condition.
condition_list ::= condition_list logical_symbols condition.

logical_symbols ::= KW_AND.
logical_symbols ::= KW_OR.

compute_symbols ::= KW_ADD.
compute_symbols ::= KW_SUB.
compute_symbols ::= KW_STAR.
compute_symbols ::= KW_DIV.

compare_symbols ::= KW_EQUAL.
compare_symbols ::= KW_NOTEQUAL.
compare_symbols ::= KW_MORE.
compare_symbols ::= KW_MEQ.
compare_symbols ::= KW_LESS.
compare_symbols ::= KW_LEQ.

compute_item ::= KW_ID.
compute_item ::= value.
compute_item ::= KW_LB compute_exp KW_RB.


condition ::= compute_exp compare_symbols compute_exp.
compute_exp ::= compute_item.
compute_exp ::= compute_exp compute_symbols compute_item.














