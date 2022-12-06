mod common;
mod days;

use clap::Parser;
use std::path::PathBuf;

use crate::{days::Challenge, days::*};

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// Simple hello world program for testing
    #[arg(long, default_value_t = false)]
    hello_world: bool,

    /// Display all output 
    #[arg(short, long, default_value_t = false)]
    verbose: bool,

    /// The day number of the challenge
    #[arg(short, long)]
    challenge: usize,

    /// The path to the input to use for the challenge
    #[arg(short, long)]
    input_path: Option<PathBuf>,
}

fn main() {
    let challenges: Vec<&dyn Challenge> = vec![&day1::Day1(), &day2::Day2(), &day3::Day3(), &day4::Day4(), &day5::Day5()];

    let args = Args::parse();

    if args.hello_world {
        println!("Hello World!");
    }

    let challenge_option = challenges.get(args.challenge-1);

    if !challenge_option.is_none() {
        let day = challenge_option.unwrap();
        let filepath = args.input_path.unwrap();
        println!("-------- Day {} Challenge ---------", args.challenge);
        day.run(filepath, args.verbose);
    } else {
        println!("Challenge not found, only challenges 1 to {} are available.", challenges.len());
    }
}