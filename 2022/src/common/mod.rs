use std::{path::PathBuf, fs::File, io::Read};

// add file opening utility

pub fn file_to_string(filepath: PathBuf) -> String {
    let display = filepath.display();
    let mut file = match File::open(&filepath) {
        Err(why) => panic!("Could not open {}: {}", display, why),
        Ok(file) => file,
    };

    let mut s = String::new();
    match file.read_to_string(&mut s) {
        Err(why) => panic!("Could not read {}: {}", display, why),
        Ok(_) => println!("Reading {}", display),
    }

    return s;
}