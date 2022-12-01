use crate::{common::Challenge, common::file_to_string};
use std::path::PathBuf;

pub struct Day1 ();

impl Challenge for Day1 {
    fn run(&self, filepath: PathBuf) {
        println!("Day 1 Challenge \n Part 1:");
        let input = file_to_string(filepath);

        println!("{}", input);
    }
}
