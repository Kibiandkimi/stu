use std::io::{Read, stdin};

fn main() {
    let config = read();

    let res = solve(config);

    for i in res {
        println!("{i}");
    }
}

struct Config {
    n: u32,
    opts: Vec<Opt>
}

enum Opt{
    M {l: u32, r: u32},
    Q {l: u32, r: u32},
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
    let mut s = input.split_whitespace();
    let n = s.next().unwrap().parse().unwrap();
    let m = s.next().unwrap().parse().unwrap();
    input = String::new();

    let mut config = Config {n, opts:Vec::with_capacity(m)};
    for _ in 0..m {
        stdin().read_line(&mut input).unwrap();
        s = input.split_whitespace();
        let opt_type_input: u32 = s.next().unwrap().parse().unwrap();
        let opt;
        let l: u32 = s.next().unwrap().parse().unwrap();
        let r: u32 = s.next().unwrap().parse().unwrap();
        opt = match opt_type_input {
            1 => { Opt::M {l, r}},
            2 => { Opt::Q {l, r}},
            _ => panic!("Error operation types!"),
        };
        config.opts.push(opt);
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

fn solve(config: Config) -> Vec<u32> {
    let mut res = Vec::new();
    let mut bit_left = BIT::new(config.n as usize);
    let mut bit_right = BIT::new(config.n as usize);

    for i in config.opts {
        match i {
            Opt::M {l, r} => {
                bit_left.add(l as usize, 1);
                bit_right.add(r as usize, 1);
            },
            Opt::Q {l, r} => {
                res.push(bit_left.query(r as usize) - bit_right.query(l as usize - 1));
            }
        }
    };

    res
}