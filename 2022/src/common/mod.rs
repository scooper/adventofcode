use std::path::PathBuf;

pub trait Challenge {
    fn run(&self, filepath: PathBuf);
}