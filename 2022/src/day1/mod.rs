use crate::{common::Challenge, common::file_to_string};
use std::path::PathBuf;

pub struct Day1 ();

struct Elf {
    num: i32,
    calories: i32,
}

impl Challenge for Day1 {
    fn run(&self, filepath: PathBuf) {
        println!("-------- Day 1 Challenge ---------\nPart 1:");
        let input = file_to_string(filepath);

        let input_split = input.split("\r\n");

        let mut elf_num: i32 = 1;
        let mut elves: Vec<Elf> = vec![Elf { num: elf_num, calories: 0 }];

        for line in input_split {
            if line.trim().is_empty() {
                elf_num +=1;
                elves.push(Elf { num: elf_num, calories: 0 });
                continue;
            }

            let len = elves.len();
            elves[len-1].calories += line.parse::<i32>().unwrap();
        }

        let mut most_caloried_elf: &Elf = elves.first().unwrap();
        for (_, elf) in elves.iter().enumerate() {
            println!("Elf {} calories: {}", elf.num, elf.calories);
            if elf.calories > most_caloried_elf.calories {
                most_caloried_elf = elf;
            }
        }

        println!("Elf {} has most calories @ {}", most_caloried_elf.num, most_caloried_elf.calories);
    }
}
