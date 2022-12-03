use crate::{common::Challenge, common::file_to_string};
use std::{path::PathBuf, vec};

pub struct Day2 ();

struct Game {
    first: char,
    second: char,
    part_1_score: i32,
    part_2_score: i32,
}

impl Challenge for Day2 {
    fn run(&self, filepath: PathBuf) {
        let input = file_to_string(filepath);
        let input_split = input.split("\n");

        let mut games: Vec<Game> = vec![];

        let mut part1_total_score = 0;
        let mut part2_total_score = 0;

        for line in input_split {
            if line.trim().is_empty() {
                continue;
            }

            let line_chars: Vec<char> = line.chars().collect();
            let first = line_chars[0];
            let second = line_chars[2];

            // part 1 score rules
            // Rock(A, X), Paper(B, Y), Scissors(C, Z)
            // 6 if you won, 3 if you draw (+ an extra 1 for playing rock, 2 for paper and 3 for scissors)

            let mut part_1_score = 0;

            // part 1
            match second {
                'X' => {
                    if first == 'A' { // draw
                        part_1_score+=3;
                    } else if first == 'C' { // win
                        part_1_score+=6;
                    }
                    part_1_score+=1;
                },
                'Y' => {
                    if first == 'B' { // draw
                        part_1_score+=3;
                    } else if first == 'A' { // win
                        part_1_score+=6;
                    }
                    part_1_score+=2;
                },
                'Z' => {
                    if first == 'C' { // draw
                        part_1_score+=3;
                    } else if first == 'B' { // win
                        part_1_score+=6;
                    }
                    part_1_score+=3;
                },
                _   => (),
            }

            // part 2
            let mut part_2_score = 0;

            match second {
                'X' => { // need to lose
                    match first {
                        'A' => part_2_score+=3,
                        'B' => part_2_score+=1,
                        'C' => part_2_score+=2,
                        _ => ()
                    }
                },
                'Y' => { // need to draw
                    part_2_score += 3;
                    match first {
                        'A' => part_2_score+=1,
                        'B' => part_2_score+=2,
                        'C' => part_2_score+=3,
                        _ => ()
                    }
                },
                'Z' => { // need to win
                    part_2_score += 6;
                    match first {
                        'A' => part_2_score+=2,
                        'B' => part_2_score+=3,
                        'C' => part_2_score+=1,
                        _ => ()
                    }
                },
                _ => ()
            }

            part1_total_score += part_1_score;
            part2_total_score += part_2_score;

            let game = Game { first, second, part_1_score, part_2_score: part_2_score};
            println!("First: {}, Second: {}, Score (1): {}, Score(2): {}", game.first, game.second, game.part_1_score, game.part_2_score);
            games.push(game);
        }

        println!("Part 1:");
        println!("Total score: {}", part1_total_score);
        println!("Part 2:");
        println!("Total score: {}", part2_total_score);

        

    }
}