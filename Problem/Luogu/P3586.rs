use std::io::{Read, stdin};

enum Opt {
    U {k:u32, a:u32},
    Z {c:u32, s:u32},
}
struct Config {
    n: u32,
    opt: Vec<Opt>
}

fn main () {
    let config = read();
    let ans = solve(config);
    for i in ans {
        println!("{}", if i {"TAK"} else {"NIE"});
    }
}

struct Rnd {
    seed: u32
}

impl Rnd {
    // #[allow(arithmetic_overflow)]
    fn rand(&mut self) ->u32 {
        let mut temp = self.seed as u64;
        temp = temp * temp;
        temp = temp % 1000000000;
        self.seed = temp as u32;
        self.seed
    }
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

fn read_char() -> char {
    let mut c = getchar();
    while c != 'U' && c != 'Z' {
        c = getchar();
    }
    c
}

fn read() -> Config {
    let n = read_int();
    let m = read_int();

    let mut config = Config {n, opt: Vec::new()};
    config.opt.reserve(m as usize);

    for _ in 0..m {
        let c = read_char();
        let a = read_int();
        let b = read_int();
        config.opt.push(match c {
            'U' => Opt::U {k:a, a:b},
            'Z' => Opt::Z {c:a, s:b},
            _ => panic!("Error reading Opt!")
        })
    }

    config
}

// TODO turn Box<Option<FTN>> into Option<Box<FTN>> may speed up ??
struct FhqTreapNode {
    value:u32,
    rnk:u32,
    siz:u32,
    sum:u64,
    ls: Box<Option<FTN>>,
    rs: Box<Option<FTN>>,
}

type FTN = FhqTreapNode;
struct FhqTreap{
    rt: Box<Option<FTN>>,
    rnd: Rnd
}

impl FTN {
    fn update(&mut self) {
        self.siz = FTN::size(&*self.ls) + FTN::size(&*self.rs) + 1;
        self.sum = FTN::get_sum(&*self.ls) + FTN::get_sum(&*self.rs) + self.value as u64;
    }

    fn size(u: &Option<FTN>) -> u32 {
        match u {
            Some(node)=> node.siz,
            None=>0
        }
    }

    fn get_sum(u : &Option<FTN>) -> u64 {
        match u {
            Some(node)=> node.sum,
            None=> 0
        }
    }

    fn get_value(u: &Option<FTN>) -> u32 {
        match u {
            Some(node)=> node.value,
            None=> 0
        }
    }

    fn split(mut self, k: u32) -> (Option<FTN>, Option<FTN>) {
        if self.value <= k {
            let mut l = None;
            let mut r = None;
            if let Some(rs) = *self.rs{
                (l, r) = rs.split(k);
            }
            self.rs = Box::new(l);
            self.update();
            (Some(self), r)
        } else {
            let mut r = None;
            let mut l = None;
            if let Some(ls) = *self.ls {
                (l, r) = ls.split(k);
            }
            self.ls = Box::new(r);
            self.update();
            (l, Some(self))
        }
    }

    fn split_by_rnk(mut self, rnk: u32) -> (Option<FTN>, Option<FTN>) {
        if self.siz < rnk {
            std::process::exit(2);
            panic!("rnk is out of range!");
        }
        if Self::size(&self.ls) >= rnk {
            let (mut l, mut r) = (None, None);
            if let Some(ls) = *self.ls {
                (l, r) = ls.split_by_rnk(rnk);
            }
            self.ls = Box::new(r);
            self.update();
            (l, Some(self))
        } else {
            let (mut l, mut r) = (None, None);
            if let Some(rs) = *self.rs {
                (l, r) = rs.split_by_rnk(rnk - FTN::size(&self.ls) - 1);
            }
            self.rs = Box::new(l);
            self.update();
            (Some(self), r)
        }
    }

    fn merge(l: Option<Self>, r: Option<Self>) -> Option<FTN> {
        if l.is_none() {
            return r;
        }
        if r.is_none() {
            return l;
        }
        let mut l = l.unwrap_or_else(|| std::process::exit(2));
        let mut r = r.unwrap_or_else(|| std::process::exit(2));
        if l.rnk > r.rnk {
            *l.rs = FTN::merge(*l.rs, Some(r));
            l.update();
            return Some(l);
        }
        *r.ls = FTN::merge(Some(l), *r.ls);
        r.update();
        Some(r)
    }
}

impl FhqTreap {
    fn insert(mut self, value: u32) -> Self {
        let new_node = Some(FTN {
            value,
            rnk: self.rnd.rand(),
            siz: 1,
            sum: value as u64,
            ls: Box::new(None),
            rs: Box::new(None)
        });

        if self.rt.is_none() {
            self.rt = Box::new(new_node);
            return self;
        }

        let (l, r) = self.rt.unwrap().split(value);

        self.rt = Box::new(FTN::merge(FTN::merge(l, new_node), r));
        self
    }

    fn query_rnk(mut self, value: u32) -> (Self, u32) {
        if value == 0 {
            return (self, 1);
        }
        let (l, r) = self.rt.unwrap_or_else(|| std::process::exit(3)).split(value - 1);
        let res = FTN::size(&l) + 1;
        self.rt = Box::new(FTN::merge(l, r));
        (self, res)
    }

    fn remove(mut self, value: u32) -> Self {
        if value == 0 {
            let (_, ret) = self.rt.unwrap_or_else(|| std::process::exit(41)).split_by_rnk(1);
            self.rt = Box::new(ret);
            return self;
        }
        let (l, r) = self.rt.unwrap_or_else(|| std::process::exit(42)).split(value - 1);
        let (_, r) = r.unwrap_or_else(|| std::process::exit(43)).split_by_rnk(1);
        // let (_, r) = r.unwrap().split_by_rnk(1);
        self.rt = Box::new(FTN::merge(l, r));
        self
    }

    fn query_sum(mut self, value: u32) -> (Self, u64) {
        let (l, r) = self.rt.unwrap_or_else(|| std::process::exit(5)).split(value);
        let res = FTN::get_sum(&l);
        self.rt = Box::new(FTN::merge(l, r));
        (self, res)
    }
}

fn solve(config: Config) -> Vec<bool> {
    let mut res:Vec<bool> = Vec::new();
    let mut list:Vec<u32> = Vec::new();
    list.resize(config.n as usize, 0);

    let mut treap = FhqTreap{rt: Box::new(None), rnd: Rnd{seed: 1145141}};

    for i in &list {
        treap = treap.insert(*i);
    }

    for i in config.opt {
        match i {
            Opt::U{k, a} => {
                treap = treap.remove(list[k as usize - 1]);
                treap = treap.insert(a);
                list[k as usize - 1] = a;
            },
            Opt::Z{c, s} => {
                let sum;
                let rnk;
                (treap, sum) = treap.query_sum(s);
                (treap, rnk) = treap.query_rnk(s + 1);
                res.push(
                    sum + (config.n - (rnk - 1)) as u64 * s as u64
                    >= c as u64 * s as u64
                );
            }
        }
    }

    res
}

#[cfg(test)]
mod tests {
    use crate::*;

    #[test]
    fn test_ftn() {
        // let mut rng = rand::thread_rng();
        let mut node = FTN{
            value: 1,
            rnk: 1,
            siz: 1,
            sum: 1,
            ls: Box::new(None),
            rs: Box::new(None)
        };

        *node.ls = Some(FTN{
            value: 0,
            rnk: 1,
            siz: 1,
            sum: 0,
            ls: Box::new(None),
            rs: Box::new(None)
        });

        *node.rs = Some(FTN{
            value: 3,
            rnk: 1,
            siz: 1,
            sum: 3,
            ls: Box::new(None),
            rs: Box::new(None)
        });

        node.update();

        assert_eq!(node.sum, 4);
        assert_eq!(node.siz, 3);

        let (Some(p), Some(q)) = node.split(1) else {
            panic!("test error in split!")
        };
        assert_eq!(p.sum, 1);
        assert_eq!(p.siz, 2);
        assert_eq!(q.sum, 3);
        assert_eq!(q.siz, 1);

        let Some(rt) = FTN::merge(Some(p), Some(q)) else {
            panic!("test error in merge!")
        };
        assert_eq!(rt.sum, 4);
    }

    #[test]
    fn test_ft() {
        let treap = FhqTreap{rt: Box::new(None), rnd: Rnd{seed: 12345678}};
        let treap = treap.insert(123456);
        let (treap, res) = treap.query_sum(123456);
        assert_eq!(res, 123456);
        let treap = treap.insert(1234567);
        let (treap, res) = treap.query_rnk(1234567);
        assert_eq!(res, 2);
        let treap = treap.remove(123456);
        let (treap, res) = treap.query_rnk(1234567);
        assert_eq!(res, 1);
    }

    #[test]
    fn test_solve() {
        let config = Config{
            n: 3,
            opt: vec![
                Opt::U{k:1, a:5},
                Opt::U{k:2, a:7},
                Opt::Z{c:2, s:6},
                Opt::U{k:3, a:1},
                Opt::Z{c:2, s:6},
                Opt::U{k:2, a:2},
                Opt::Z{c:2, s:6},
                Opt::Z{c:2, s:1}
            ]
        };

        let result = solve(config);
        for i in result {
            println!("{}", if i {"TAK"} else {"NIE"});
        }
    }

    // #[test]
    // fn test_getchar() {
    //     let c = getchar();
    //     println!("{}", c);
    // }

    #[test]
    fn test_ft2() {
        let mut treap = FhqTreap{rt: Box::new(None), rnd: Rnd{seed: 998244353}};
        treap = treap.insert(0);
        treap = treap.insert(1);
        treap = treap.insert(2);
        treap = treap.insert(0);
        treap = treap.insert(2);
        treap = treap.insert(2);
        treap = treap.insert(0);
        // treap = treap.insert(1000000000);
        // treap = treap.insert(1000000000);
        // treap = treap.insert(1000000000);
        treap = treap.insert(0);
        treap = treap.remove(2);
        // treap = treap.insert(1000000000);
        // treap = treap.remove(1000000000);
        treap = treap.remove(0);
        treap = treap.insert(0);
        // treap = treap.remove(2);
        // treap = treap.insert(0);
        // treap = treap.remove(1000000000);
        // treap = treap.remove(2);
        // treap = treap.remove(1000000000);
        // treap = treap.remove(0);
        // treap = treap.remove(2);
        // treap = treap.remove(0);
        // treap = treap.remove(1000000000);
        // treap = treap.remove(1);
        // treap = treap.remove(0);

    }
}
