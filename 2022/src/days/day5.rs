use crate::{days::Challenge, common::file_to_string};
use std::{path::PathBuf, collections::VecDeque};

pub struct Day5 ();

impl Challenge for Day5 {
    fn run(&self, filepath: PathBuf, verbose_output: bool) {
        let input = file_to_string(filepath);
        let input_split = input.split_terminator("\n");
        
        let mut stacks_p1: Vec<VecDeque<char>> = vec![];
        let mut stacks_p2: Vec<VecDeque<char>> = vec![];

        let mut first_move = true;

        for line in input_split {
            if line.trim().is_empty() {
                if verbose_output {
                    println!("\nStart Stacks: {:?}", stacks_p1);
                }
                continue;
            }

            if line.contains("[") {
                // init stacks
                // calculates num of stacks based fitting 4 characters '[C] ' (the box and a space)
                // into the first encountered string multiple times, it'll always give you the number of
                // available boxes -1 (because no trailing space) so we add 1 at the end
                if stacks_p1.len() == 0 {
                    let num_stacks = ((line.len()-1) / 4) + 1;

                    if verbose_output {
                        println!("Num stacks: {}", num_stacks);
                    }

                    for _ in 0..num_stacks {
                        let stack: VecDeque<char> = VecDeque::from(vec![]);
                        stacks_p1.push(stack);
                    }
                }

                let linechars: Vec<char> = line.chars().collect();

                let mut stack_index = 0;
                for i in (1..linechars.len()).step_by(4) {
                    if linechars[i].is_alphabetic() {
                        if verbose_output {
                            print!("{}({}) ", linechars[i], stack_index);
                        }

                        stacks_p1[stack_index].push_back(linechars[i]);
                    }
                    stack_index += 1;
                }
            }

            if line.starts_with("m") {
                if first_move {
                    stacks_p2 = stacks_p1.clone();
                    first_move = false;
                }

                let split: Vec<&str> = line.trim().split(" ").collect(); // trim \r may be necessary depending on system
                let mov = split[1].parse::<usize>().unwrap();
                let from = split[3].parse::<usize>().unwrap();
                let to = split[5].parse::<usize>().unwrap();

                if verbose_output {
                    println!("Moving {} from {} to {}", mov, from, to);
                }

                // part 1
                for _ in 0..mov {
                    let elem = stacks_p1[from-1].pop_front().unwrap();
                    stacks_p1[to-1].push_front(elem);
                }

                // part 2
                for i in 0..mov {
                    let index = (mov-1) - i;
                    let elem = stacks_p2[from-1].remove(index).unwrap();
                    stacks_p2[to-1].push_front(elem);
                }
            }
        }

        println!("Part 1:");

        if verbose_output {
            println!("End Stacks (P1) {:?}", stacks_p1);
            println!("End Stacks (P2) {:?}", stacks_p2);
        }

        let mut part1_str = "".to_string();
        for stack in stacks_p1 {
            part1_str.push_str(&stack.front().unwrap().to_string());
        }

        println!("First of each stack = {}", part1_str);

        println!("Part 2:");

        let mut part2_str = "".to_string();
        for stack in stacks_p2 {
            part2_str.push_str(&stack.front().unwrap().to_string());
        }

        println!("First of each stack = {}", part2_str);
    }
}