/// # Expression
///
/// Represents a single expression in the AST.
#[derive(Debug,PartialEq)]
pub enum Expression {
    StringLiteral(String),
    NumberLiteral(i64)
}


impl Expression {
    
    pub fn new_int_literal(value: i64) -> Expression {
        Expression::NumberLiteral(value)
    }

    pub fn new_str_literal(value: String) -> Expression {
        Expression::StringLiteral(value)
    }
}
