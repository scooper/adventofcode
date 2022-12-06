use crate::{days::Challenge, common::file_to_string};
use std::path::PathBuf;

pub struct Day4 ();

impl Challenge for Day4 {
    fn run(&self, filepath: PathBuf, verbose_output: bool) {
        let input = file_to_string(filepath);
        let input_split = input.split_whitespace();
        
        let mut fully_contained_pairs = 0;
        let mut any_overlap_pairs = 0;
        for line in input_split {

            if line.trim().is_empty() {
                continue;
            }

            let (elf1, elf2) = line.split_once(",").unwrap();   

            let (elf1_start, elf1_end) = elf1.split_once("-")
                .map(|(str1, str2)| (str1.parse::<i32>().unwrap(), str2.parse::<i32>().unwrap()))
                .unwrap();
            let (elf2_start, elf2_end) = elf2.split_once("-")
                .map(|(str1, str2)| (str1.parse::<i32>().unwrap(), str2.parse::<i32>().unwrap()))
                .unwrap();

                
            let mut fully_contained = false;
            let mut partial_contained = false;
            
            if elf1_start <= elf2_start && elf1_end >= elf2_end || elf2_start <= elf1_start && elf2_end >= elf1_end {
                fully_contained_pairs += 1;
                fully_contained = true;
            }

            if elf1_start <= elf2_end && elf2_start <= elf1_end {
                any_overlap_pairs += 1;
                partial_contained = true;
            }
            
            if verbose_output {
                println!("Elf1: {}-{} Elf2: {}-{}, Fully Contained = {}, Partial Contained = {}",
                elf1_start, elf1_end, elf2_start, elf2_end, fully_contained, partial_contained);
            }
                
        }

        println!("Part 1:");
        println!("Num fully contained pairs = {}", fully_contained_pairs);
        println!("Part 2:");
        println!("Num of any overlap pairs = {}", any_overlap_pairs);
    }
}