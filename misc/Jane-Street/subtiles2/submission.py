"""
Found solutions: 1
a=1/4, b=-3, c=1/2, p=5, n=6
"""

import sympy as sp, math, itertools, time
a=sp.Symbol('a')
b=sp.Symbol('b', integer=True)
c=sp.Symbol('c')
# rebuild exprs minimal needed (25)
exprs_list=[
('r1c5',6*c-4*b),
('r2c8',8-b),
('r3c2',(a**b-4)/(6*c+1)),
('r3c4',(b+c)/(c-1)),
('r3c7',b**2-b/c),
('r3c9',sp.sqrt(30+a)/c),
('r3c11',(a+b)/(c-3*a)),
('r4c5',(b-3*a)/(a-c)),
('r4c8',8*a-2*b),
('r4c10',b/(a-c)),
('r4c12',(b+9)/sp.sqrt(c-a)),
('r5c2',18/(a*c+1)),
('r5c6',c**b),
('r5c11',(3+b**2)/sp.sqrt(3+2*c)),
('r6c4',b/(a**2-c**2)),
('r6c13',sp.sqrt(a+2)/a),
('r7c3',a**b-12/a),
('r7c5',2*c+c/a),
('r7c7',4*a-5*b),
('r7c9',c+2*a),
('r7c11',b/(9*a-5*c)),
('r8c1',(b**3+2*c)/(b+2*c)),
('r8c10',b/(a-1)),
('r9c3',(c-b)/(2*a)),
('r9c8',b/(a-c)),
('r9c12',(b+c)/(a-c)),
('r10c2',sp.log(a,c)),
('r10c4',(c**2-b)/a),
('r10c6',(b-1)**2),
('r10c9',sp.real_root(43-a*c,3)/a),
('r11c3',(b-a)/(a-c)),
('r11c5',11-b),
('r11c7',(b-2*a)/(a-c)),
('r11c10',(c+3)/a),
('r11c12',8*c-b/c),
('r12c6',b**2),
('r13c9',(2**b+1)/(a*c)),
]
def pos_int_exact(expr):
    expr_s=sp.simplify(expr)
    if expr_s.is_real is False:
        return False
    if expr_s.is_Integer:
        return int(expr_s)>0
    if expr_s.is_Rational:
        return expr_s.q==1 and expr_s>0
    return False

def all_pos_int(subs):
    for name,e in exprs_list:
        ev=sp.simplify(e.subs(subs))
        if not pos_int_exact(ev):
            return False
    return True

start=time.time()
solutions=[]
for bval in range(-15,8):
    if bval==0: 
        continue
    # bval must make 8-b positive so b<8 always ok. also 11-b positive => b<11 ok.
    for nval in range(1,11):
        # enforce r6c13 integer nval by solving for a
        # equation sqrt(a+2)/a = nval => a = (1+sqrt(1+8n^2))/(2n^2)
        aval=(1+sp.sqrt(1+8*nval**2))/(2*nval**2)
        # quick reject: a shouldn't be 1 (div by 0 in r8c10)
        if sp.simplify(aval-1)==0:
            continue
        # need sqrt(30+a) real so a>-30 (true)
        # choose pval such that r3c4 integer pval and derive c
        for pval in range(-20,21):
            if pval==1: 
                continue
            cval=sp.Rational(bval+pval,pval-1)  # from (b+c)/(c-1)=p
            if cval<=0:
                continue
            # require c-a positive for sqrt(c-a)
            if float(sp.N(cval-aval))<=0:
                continue
            subs={a:aval,b:bval,c:cval}
            # quick checks for a few expressions to be positive integers
            quick_names=['r2c8','r11c5','r4c8','r3c4','r6c13','r10c6']
            ok=True
            for name,e in exprs_list:
                if name in quick_names:
                    ev=sp.simplify(e.subs(subs))
                    if not pos_int_exact(ev):
                        ok=False; break
            if not ok:
                continue
            if all_pos_int(subs):
                solutions.append((aval,bval,cval,pval,nval))
end=time.time()
len(solutions), end-start

print("Found solutions:",len(solutions))
for sol in solutions:
    aval,bval,cval,pval,nval=sol
    print(f"a={aval}, b={bval}, c={cval}, p={pval}, n={nval}")
