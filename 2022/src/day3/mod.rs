use crate::{common::Challenge, common::file_to_string};
use std::{path::PathBuf, vec};

pub struct Day3 ();

impl Challenge for Day3 {
    fn run(&self, filepath: PathBuf, verbose_output: bool) {
        let input = file_to_string(filepath);
        let input_split = input.split("\n");

        let mut total_priority_p1: u32 = 0;
        let mut total_priority_p2: u32 = 0;

        let mut current_intersection_p2: Vec<char> = vec![];
        for (i, line) in input_split.enumerate() {

            // p2 calculate priority
            if i % 3 == 0 {
                if !current_intersection_p2.is_empty() {
                    let priority_p2 = get_priority(current_intersection_p2[0]);
                    total_priority_p2 += priority_p2;

                    // p2 output
                    if verbose_output {
                        println!("P2: Rucksack {} - {}, Priority = {}", i-2, i, priority_p2);
                    }
                }       
            }

            // if input is empty (end of input), dont execute
            if line.trim().is_empty() {
                continue;
            }

            let contents: Vec<char> = line.trim().chars().collect();

            // p2 intersection
            if i % 3 == 0 {
                current_intersection_p2 = contents.clone();
            } else {
                current_intersection_p2 = current_intersection_p2.iter().filter(|&x| contents.contains(x)).cloned().collect();
            }

            // p1 intersection
            let contents_first = &contents[0..contents.len()/2];
            let contents_second = &contents[contents.len()/2..contents.len()];

            let intersection_p1: Vec<char> = contents_first.iter().filter(|&x| contents_second.contains(x)).cloned().collect();

            let priority_p1 = get_priority(intersection_p1[0]);
            total_priority_p1 += priority_p1;

            // p1 output
            if verbose_output {
                println!("P1: Rucksack {}, Priority = {}", i+1, priority_p1);
            }
        }

        println!("Part 1:");
        println!("Total Priority = {}", total_priority_p1);

        println!("Part 2:");
        println!("Total Priority = {}", total_priority_p2);


    }
}

fn get_priority(c: char) -> u32 {
    if !c.is_alphabetic() {
        return 0;
    }
    let ascii_value = c as u32;

    if c.is_uppercase() {
        return ascii_value - 38; // work this out
    } else {
        return ascii_value - 96;
    }
}