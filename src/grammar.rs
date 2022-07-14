use crate::ast::Expression;
use std::str::FromStr;

peg::parser!{
    pub grammar natterjack() for str {
        pub rule expression() -> Expression
            = spmany() expr:expr_prime() spmany() { expr }

        rule expr_prime() -> Expression
            = nvalue:number_lit() { Expression::new_int_literal(nvalue) }
            / svalue:string_lit() { Expression::new_str_literal(svalue) }

        // number literals
        rule number_lit() -> i64
            = "0x" c:$(hex_char()+) { i64::from_str_radix(c, 16).unwrap() }
            / "0b" c:$(bin_char()+) { i64::from_str_radix(c, 2).unwrap() }
            / "0o" c:$(oct_char()+) { i64::from_str_radix(c, 8).unwrap() }
            / c:$(dec_char()+) { i64::from_str(c).unwrap() }

        rule bin_char() -> char = ['0'|'1']
        rule oct_char() -> char = ['0'..='8']
        rule hex_char()  -> char= dec_char() / ['A'..='F' | 'a' ..= 'f']
        rule dec_char()  -> char= ['0'..='9']

        // string literals
        rule string_lit() -> String
            = "\"" c:$(string_char()*) "\"" { c.to_string() }

        // TODO: support escaping here..
        rule string_char() -> char = [^'"'] 

        // whitespace handling
        rule nl_char() = ['\r'|'\n']
        rule sp_char() = [' '|'\t']
        rule spone() = sp_char() / nl_char()
        rule spmany() = spone()*
    }
}