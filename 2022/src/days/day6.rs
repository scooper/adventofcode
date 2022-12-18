use crate::{days::Challenge, common::file_to_string, common::is_unique};
use std::path::PathBuf;

pub struct Day6 ();

impl Challenge for Day6 {
    fn run(&self, filepath: PathBuf, verbose_output: bool) {
        let input = file_to_string(filepath);
        
        let input_buff: Vec<char> = input.trim().chars().collect();

        let mut chars_buff_p1: Vec<char> = vec![];
        let mut chars_buff_p2: Vec<char> = vec![];

        let mut part1_index = 0;
        let mut part2_index = 0;

        // maintain a collection of 4 characters, checking if they can be a marker each time 
        for (i, c) in input_buff.into_iter().enumerate() {
            chars_buff_p1.insert(0, c);
            chars_buff_p2.insert(0, c);

            if chars_buff_p1.len() > 4 {
                chars_buff_p1.pop();
            }

            if chars_buff_p2.len() > 14 {
                chars_buff_p2.pop();
            }

            if is_unique(&chars_buff_p1) && chars_buff_p1.len() == 4 {
                if verbose_output {
                    println!("Marker (P1) at {}", i);
                }

                if part1_index == 0 {
                    part1_index = i+1;
                }
            }

            if is_unique(&chars_buff_p2) && chars_buff_p2.len() == 14 {
                if verbose_output {
                    println!("Marker (P2) at {}", i);
                }

                if part2_index == 0 {
                    part2_index = i+1;
                }
            }

            if verbose_output {
                println!("{:?}", chars_buff_p1);
            }
        }

        println!("Part 1:");
        println!("First start-of-packet marker after character {}", part1_index);
        println!("Part 2:");
        println!("First start-of-message marker after character {}", part2_index);

    }
}