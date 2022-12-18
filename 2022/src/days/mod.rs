use std::path::PathBuf;

pub mod day1;
pub mod day2;
pub mod day3;
pub mod day4;
pub mod day5;
pub mod day6;

pub trait Challenge {
    fn run(&self, filepath: PathBuf, verbose_output: bool);
}