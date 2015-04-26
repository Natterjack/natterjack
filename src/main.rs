#![feature(plugin,collections,str_char)]
#![plugin(peg_syntax_ext)]

mod ast;

peg_file! parser("grammar.rustpeg");

#[cfg(not(test))]
fn main() {
    println!("Nothing to see here, move on :-p");
}

#[cfg(test)]
mod test {
    use super::parser::expression;
    use super::ast;

    fn check_literal(input: &str, expected: i64) {
        let parsed = expression(input).unwrap();
        assert_eq!(parsed, ast::Expression{ value: expected });
    }

    #[test]
    fn test_parse_literal_numbers() {
        check_literal("1", 1);
        check_literal("1337", 1337);
        check_literal("100", 100);
        check_literal("1701", 1701);
        let max_str = format!("{}", ::std::i64::MAX);
        check_literal(&max_str, ::std::i64::MAX);
    }
}
