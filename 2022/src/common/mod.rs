use std::{path::PathBuf, fs::File, io::Read, hash::Hash, collections::HashSet};

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

pub fn is_unique<T>(iter: T) -> bool
where
T: IntoIterator,
T::Item: Eq + Hash,
{
    let mut unique = HashSet::new();
    iter.into_iter().all(move |x| unique.insert(x))
}