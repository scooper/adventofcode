use crate::{days::Challenge, common::file_to_string};
use std::path::PathBuf;

pub struct Day5 ();

impl Challenge for Day5 {
    fn run(&self, filepath: PathBuf, verbose_output: bool) {
        let input = file_to_string(filepath);
        let input_split = input.split_whitespace();
        
    }
}