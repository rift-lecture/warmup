define i32 @aFun(i32 %n) {
entry:
  %tst = icmp slt i32 %n, 2
  br i1 %tst, label %tr, label %fs
tr:
  br label %cont

fs:
  %m1 = sub i32 %n, 1
  %m2 = sub i32 %m1, 1
  %fib1 = call i32 @aFun(i32 %m1)
  %fib2 = call i32 @aFun(i32 %m2)
  %fres = add i32 %fib1, %fib2
  br label %cont

cont:
  %res = phi i32 [1, %tr], [%fres, %fs]
  ret i32 %res
}
