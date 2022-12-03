mod common;
mod day1;
mod day2;

use clap::Parser;
use std::path::PathBuf;

use crate::{common::Challenge, day1::Day1, day2::Day2};

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// simple hello world program
    #[arg(long, default_value_t = false)]
    hello_world: bool,

    /// the day number of the challenge
    #[arg(short, long)]
    challenge: usize,

    /// the path to the input to use for the challenge
    #[arg(short, long)]
    input_path: Option<PathBuf>,
}

fn main() {
    let challenges: Vec<&dyn Challenge> = vec![&Day1(), &Day2()];

    let args = Args::parse();

    if args.hello_world {
        println!("Hello World!");
    }

    let challenge_option = challenges.get(args.challenge-1);

    if !challenge_option.is_none() {
        let day = challenge_option.unwrap();
        let filepath = args.input_path.unwrap();
        println!("-------- Day {} Challenge ---------", args.challenge);
        day.run(filepath);
    } else {
        println!("Challenge not found, only challenges 1 to {} are available.", challenges.len());
    }
}