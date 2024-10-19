use std::io::{Read, stdin};
use std::cmp::max;

fn main() {
    let config = read();

    let res = solve(config);

    println!("{res}");
}

struct Config {
    arr: Vec<u32>
}

fn getchar() -> char {
    let stdin = stdin();
    let mut handle = stdin.lock();

    let mut buffer = [0; 1];

    handle.read_exact(&mut buffer);

    let c = buffer[0] as char;

    if c.is_ascii() {
        return c;
    }
    std::process::exit(1);
    panic!("Error reading char!");
}

fn read_int() -> u32 {
    let mut c = getchar();
    let mut s = 0;
    while c < '0' || '9' < c {
        c = getchar();
    }
    while '0' <= c && c <= '9' {
        s = s * 10 + (c as u32 - '0' as u32);
        c = getchar();
    }
    s
}

fn read_str() -> String {
    let mut str = String::new();
    let mut c = getchar();
    while c < 'a' || 'z' < c {
        c = getchar();
    }
    while 'a' <= c && c <= 'z' {
        str.push(c);
        c = getchar();
    }
    str
}

fn read_char() -> char {
    let mut c = getchar();
    while c != 'Q' && c != 'R' && c != 'I' && (c < 'a' || c > 'z') {
        c = getchar();
    }
    c
}

fn read() -> Config {
    let mut input = String::new();
    stdin().read_line(&mut input).unwrap();
    input.pop();
    let n = input.parse().unwrap();
    input = String::new();

    let mut config = Config {arr:Vec::with_capacity(n)};
    for _ in 0..n {
        stdin().read_line(&mut input).unwrap();
        input.pop();
        let val = input.parse().unwrap();
        config.arr.push(val);
        input = String::new();
    }

    config
}

fn solve(config: Config) -> usize {
    let mut res = 0;

    let mut arr:Vec<_> = (0..config.arr.len()).collect();

    arr.sort_by(|x, y| config.arr[*x].cmp(&config.arr[*y]));
    let mut k = 0;
    for i in arr {
        res = max(res, if i > k {i - k} else {0});
        k += 1;
    }

    res + 1
}