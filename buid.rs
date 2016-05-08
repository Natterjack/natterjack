extern crate syntex;
extern crate peg_syntax_ext;

fn main() {
    let mut registry = syntex::Registry::new();
    peg_syntax_ext::register(&mut registry);

    registry.expand(
        "natterjack",
        &Path::new("src/grammar.rustpeg"),
        &Path::new(os::getenv("OUT_DIR").unwrap()).join("grammar.rs"));
}
