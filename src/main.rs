mod ast;

mod grammar;

#[cfg(not(test))]
fn main() {
    println!("Nothing to see here, move on :-p");
}

#[cfg(test)]
mod test {
    use super::grammar::natterjack::expression;
    use super::ast::*;

    fn check_int_literal(input: &str, expected: i64) {
        let parsed = expression(input).unwrap();
        assert_eq!(parsed, Expression::new_int_literal(expected));
    }

    #[test]
    fn test_parse_literal_numbers() {
        check_int_literal("1", 1);
        check_int_literal("1337", 1337);
        check_int_literal("100", 100);
        check_int_literal("1701", 1701);
        let max_str = format!("{}", ::std::i64::MAX);
        check_int_literal(&max_str, ::std::i64::MAX);
    }

    #[test]
    fn test_parse_number_with_whitespace_ignores_whitespace() {
        check_int_literal(" 4", 4);
        check_int_literal("34 ", 34);
        check_int_literal("\t 123456\t ", 123456);
    }

    #[test]
    fn test_parse_hex_numbers() {
        check_int_literal("0xFF", 255);
        check_int_literal("0xa", 10);
        check_int_literal("0x123456789abc", 20_015_998_343_868);
    }

    #[test]
    fn test_parse_bin_numbers() {
        check_int_literal("0b1101", 13);
        check_int_literal("0b1111", 15);
        check_int_literal("0b111111111111111111111111111111111111111111111111111111111111111",
                          ::std::i64::MAX);
        check_int_literal("0b0", 0);
    }

    #[test]
    fn test_parse_octal_numbers() {
        check_int_literal("0o765432", 256794);
        check_int_literal("0o00", 0);
        check_int_literal("0o0000001", 1);
    }

    fn check_str_literal(input: &str, expected: String) {
        let parsed = expression(input).unwrap();
        assert_eq!(parsed, Expression::new_str_literal(expected));
    }

    #[test]
    fn test_simple_string() {
        check_str_literal(r#" "a simple string literal" "#,
                          "a simple string literal".to_string());
    }

    #[test]
    fn test_whitespace_is_preserved() {
        check_str_literal(r#""    long    string    ""#,
                          "    long    string    ".to_string());
    }

}
