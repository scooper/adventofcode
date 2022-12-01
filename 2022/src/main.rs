mod common;
mod day1;

use clap::Parser;
use std::path::PathBuf;

use crate::{common::Challenge, day1::Day1};

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// simple hello world program
    #[arg(long, default_value_t = false)]
    hello_world: bool,

    /// the day number of the challenge
    #[arg(short, long, default_value_t = 0)]
    challenge: usize,

    /// the path to the input to use for the challenge
    #[arg(short, long)]
    input_path: Option<PathBuf>,
}

fn main() {
    let challenges: Vec<&dyn Challenge> = vec![&Day1()];

    let args = Args::parse();

    if args.hello_world {
        println!("Hello World!");
    }

    let challenge_option = challenges.get(args.challenge-1);

    if !challenge_option.is_none() {
        let day = challenge_option.unwrap();
        day.run(args.input_path.unwrap());
    }
}