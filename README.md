# PasswordGenerator

#### Produce secure passwords using *Mersenne Twister*!

### To-do
1. Make it easier to use on Windows (?)

### Tips
1. Command-line flags can be combined.
    * with the exception of `-n` and `-l`
    * _eg_ `-maAs` (remove metainfo, add lowercase letters, uppercase letters, and symbols)
2. Piping output is a great way to avoid filling up your screen with text
    * _eg_ `./passgen -m -n 60 > test.txt` (put sixty 8-digit random numbers into a text file)
3. Longer length passwords are generally more secure.
    * _eg_ See below:
    ```
    ./passgen -maAs -n 20 -l 64 
    ~0+aS88c#v*0XISI8@7U5!5AJ31n61CU9z72j7s3z^ml2dC+%*z?6wg5u1C2+UK%
    Rx7%4?4cU$LY3L5#j375xO5N12BY5b7y89D8DE0Ea!UC7x=3aFfV34,t,5dods1f
    8cB0,c,9@d!3-T*~G%H@X~,NYE$1AfoOCcRg+p9$vJT@svBQBEAz,!45Dy*zce99
    J9b7ci0e^EW$-BI1s58QWXN@m3G9+y9!0^ZW6#.-Ekul3gk%QpKIE7f,411TF9ka
    =Y883t-ca72M~p,*33kgX,44zyZ0.y8z6R1O8KJ#3r9*609FAq497#dW38vo8cn0
    bP*Je=ov6.ess%^5x-z9-s@19^5V^xs^18=1Pc%t43@p.3Q91,F9!#@55H**G4aP
    =j5+88Dw4%^MV0X#67i4?=!Nlx.Y^^%^3,%mU?*A2N6E0?ix@VF!^F1o8*aBX==6
    9o7F4UlQ.W^m-56,*c2+6?1.@r@z-oST7v7~iY^@0A8k+,J?lC34RPv040hk@%08
    m4-?^+PcH73,@r7$aSqrH3g73.RKa2*b1800-F4DluSdE0y+yp+6-yE1nqH!fsKs
    ~0y9~.i*1*XqOo82?7Y*H9YJwTT6z$II8E*1,-A**3#Os12JE~Slnt@6y+^qXy*7
    h3Z!66EP1l,3^+.rm8l+*D$vqen9SU8!=M.20mLULb84+SMkBw3O~1El2=@25$T=
    $SEeB+V~-0EM8mXE88#4v8Q+5Cw=fnN9CpEI7@+91=@G^!Q+.RWt5Z3V6b#nDS2t
    36!e7W!lW77@?!*4vIYi4z8W!i0,1o%7!-?o.l4etb9#80S5.yW=.43V695DGq1.
    4%u2E33Qs4~rzl541MY8#W6v1els3m-taO2XT9Uw#9br7cP^Yp*v+bb0,auF3w76
    *~A^ODoY8A%dv0-VX-+Pp*.5-6-PAx*37~Q.T6U%qRai#7r60v@@55XAc#+4.W7L
    0FoLUm$IUVK?b9ig?2#P4^6qkS0%2v%fX%6mO+8a2-QlZe9Q,s^9KK2+Ews=3,gC
    QY?h0-5YTp19dVk^w?0GxL*39hhB,+c?q7IR~^p0~v9g~0vY#KX%TH1U33r58z9W
    =il!G7.1k$#1a=HtiV+$^1L%b@89*3QEoS*iX=s+4?7DU^O*ziT64Cta4CL4!8vT
    lwG@IVr8711pI334.e*DFDR1O4,08PZHZ9Aq*-szeujDR~tS0r7c@jf.^VWe@EV%
    6adDNR^^b~7@C89Pk1Xv%c3CKZBKB6357%A%,7kc%n*V3H=2.jgR3i0mW9Ibl058
    ```

### Installing (on a *NIX system)
1. Clone repository
2. `cd PasswordGenerator`
3. `make`
4. `./passgen -h` or `./passgen` for help and usage instructions

### Installing (on Windows)
1. Clone repository
2. Make a new, empty project in the IDE of your choice
3. Add `PasswordGenerator/main.cpp` to your source files
4. Compile and run
  * Executable can be found wherever your compiler spits it out
 
### Contributing (same as any other project, really)
1. Fork repository
2. Make desired changes to project
3. Submit pull request
