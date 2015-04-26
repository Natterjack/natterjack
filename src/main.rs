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

    #[test]
    fn test_parse_number_with_whitespace_ignores_whitespace() {
        check_literal(" 4", 4);
        check_literal("34 ", 34);
        check_literal("\t 123456\t ", 123456);
    }

    #[test]
    fn test_parse_hex_numbers() {
        check_literal("0xFF", 255);
        check_literal("0xa", 10);
        check_literal("0x123456789abc", 20_015_998_343_868);
    }

    #[test]
    fn test_parse_bin_numbers() {
        check_literal("0b1101", 13);
        check_literal("0b1111", 15);
        check_literal("0b111111111111111111111111111111111111111111111111111111111111111", ::std::i64::MAX);
        check_literal("0b0", 0);
    }

    #[test]
    fn test_parse_octal_numbers() {
        check_literal("0o765432", 256794);
        check_literal("0o00", 0);
        check_literal("0o0000001", 1);
    }
}
