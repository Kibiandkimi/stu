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

struct BIT {
    value: Vec<u32>
}

impl BIT {
    fn new(n: usize) -> Self {
        let mut bit = Self{value: Vec::new()};
        bit.value.resize(n + 1, 0);
        bit
    }

    fn add (&mut self, mut pos: usize, val: u32) {
        while pos < self.value.len() {
            self.value[pos] += val;
            pos += pos & (pos ^ (pos - 1));
        }
    }

    fn query(&self, mut pos: usize) -> u32{
        let mut res:u32 = 0;
        while pos > 0 {
            res += self.value[pos];
            pos -= pos & (pos ^ (pos - 1));
        }
        res
    }
}

struct Node {
    pos: usize,
    val: u32,
}

fn solve(config: Config) -> usize {
    let mut res = 1;

    let mut arr = Vec::with_capacity(config.arr.len());
    for i in 0..config.arr.len() {
        arr.push(Node{pos: i + 1, val: config.arr[i]});
    }

    arr.sort_by(|x, y| x.val.cmp(&y.val));
    for i in 0..arr.len() {
        arr[i].val = (i + 1) as u32;
    }
    arr.sort_by(|x, y| x.pos.cmp(&y.pos));

    let mut bit = BIT::new(arr.len());
    for i in arr {
        bit.add(i.val as usize, 1);
        res = max(res, i.pos - bit.query(i.pos) as usize);
    }

    res
}