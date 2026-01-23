# **************************************************************************** #
#                                   BUILTINS                                   #
# **************************************************************************** #

### ECHO ###

#Test Number 278 input
echo cd ~

#Test Number 279 input
echo "cd ~"

#Test Number 280 input
echo ""$?""

#Test Number 281 input
echo $?"42"

#Test Number 282 input
echo ''$?''"42"

#Test Number 283 input
echo '"$USER"'

#Test Number 284 input
echo "'$USER'"

#Test Number 285 input
echo ""'$USER'""

#Test Number 286 input
echo '"'$USER'"'

#Test Number 287 input
echo "''$USER''"

#Test Number 288 input
echo "'"'$USER'"'"

#Test Number 289 input
echo '"'"$USER"'"'

#Test Number 290 input
echo $"HOME"$USER

#Test Number 291 input
echo $"HOM"E$USER

#Test Number 292 input
echo "exit_code ->$? user ->$USER home -> $HOME"

#Test Number 293 input
echo $"HOME"

#Test Number 294 input
echo $"42$"

#Test Number 295 input
echo """"""""$USER""""""""

#Test Number 296 input
echo "$ "

#Test Number 297 input
echo hi >./outfiles/outfile01 | echo bye

#Test Number 298 input
echo <123 <456 hi | echo 42

#Test Number 299 input
echo '$='

#Test Number 300 input
echo '$ '

#Test Number 301 input
echo "$?"

#Test Number 302 input
echo '$?'

#Test Number 303 input
echo "'$?'"

#Test Number 304 input
echo \$USER

#Test Number 305 input
echo \\$USER

#Test Number 306 input
echo \\\$USER

#Test Number 307 input
echo \\\\$USER

#Test Number 308 input
echo \\\\\$USER

#Test Number 309 input
echo \\\\\\\\\$USER

#Test Number 310 input
echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \$PATH \\$PWD

#Test Number 311 input
echo "cat lol.c | cat > lol.c"

#Test Number 312 input
echo "cat lol.c '|' cat > lol.c"

#Test Number 313 input
echo '$USER' "$USER" "text  ' text"

#Test Number 314 input
echo $USER =intergalaktikus miaf*szomez

#Test Number 315 input
echo -n"-n" bonjour

#Test Number 316 input
echo "'$USER'"

#Test Number 317 input
echo " '$USER' "

#Test Number 318 input
echo text"$USER"

#Test Number 319 input
echo text"'$USER'" ' $USER '

#Test Number 320 input
echo "text"   "$USER"    "$USER"

#Test Number 321 input
echo '              $USER          '

#Test Number 322 input
echo ''''''''''$USER''''''''''

#Test Number 323 input
echo """"""""$USER""""""""

#Test Number 324 input
echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''

#Test Number 325 input
echo "text" "text$USER" ... "$USER"

#Test Number 326 input
echo

#Test Number 327 input
echo ''

#Test Number 328 input
echo ""

#Test Number 329 input
echo '' ""

#Test Number 330 input
echo echo

#Test Number 331 input
echo test1

#Test Number 332 input
echo 'test1'

#Test Number 333 input
echo "echo hallo"

#Test Number 334 input
echo echo"1"

#Test Number 335 input
echo "test1 test2"

#Test Number 336 input
echo "test1  test2" test3

#Test Number 337 input
echo " test1 test2 " 'test3 '

#Test Number 338 input
echo test1		test2

#Test Number 339 input
echo $USER$TESTNOTFOUND$HOME$

#Test Number 340 input
echo $USER$TESTNOTFOUND$HOME$WTF$PWD


#Test Number 341 input
echo -n test1

#Test Number 342 input
echo -n "test1 test2"

#Test Number 343 input
echo -n "test1 test2" test3

#Test Number 344 input
echo -n " test1 test2 " 'test3 '

#Test Number 345 input
echo -n test1		test2

#Test Number 346 input
echo test1 -n

#Test Number 347 input
echo "test1 -n"

#Test Number 348 input
echo -n -n test1

#Test Number 349 input
echo -n -n -n -n -n test1

#Test Number 350 input
echo -
#Test Number 351 input
echo --

#Test Number 352 input
echo "  -nn "

#Test Number 353 input
echo "-n test1 -n test2"

#Test Number 354 input
echo "test1 -n test2"

#Test Number 355 input
echo ~42

#Test Number 356 input
echo -n -n -nasd

#Test Number 357 input
echo -n -n -n-nnnnn

#Test Number 358 input
echo -n -nnnnnnn -n -nnn -nnnnn -n-n

#Test Number 359 input
echo -n -nnnnnnn -n -nnn -nnnnn -n feel my pain

#Test Number 360 input
echo -n -n -n-n

#Test Number 361 input
echo "'totally logical'"

#Test Number 362 input
echo 'totally logical'

#Test Number 363 input
echo ''totally logical''

#Test Number 364 input
echo ""'totally logical'""

#Test Number 365 input
eCho

#Test Number 366 input
eChO

#Test Number 367 input
eCHO

#Test Number 368 input
ECHO

### CD ###
#Test Number 369 input
pwd
#Test Number 370 input
cd
#Test Number 371 input
pwd

#Test Number 372 input
pwd
#Test Number 373 input
cd ..
#Test Number 374 input
pwd

#Test Number 375 input
cd ..
#Test Number 376 input
cd $OLDPWD

#Test Number 377 input
pwd
#Test Number 378 input
cd .
#Test Number 379 input
pwd

#Test Number 380 input
pwd
#Test Number 381 input
cd "."
#Test Number 382 input
pwd

#Test Number 383 input
pwd
#Test Number 384 input
cd /Users
#Test Number 385 input
pwd

#Test Number 386 input
pwd
#Test Number 387 input
cd //////
#Test Number 388 input
pwd

#Test Number 389 input
pwd
#Test Number 390 input
cd ./././
#Test Number 391 input
pwd

#Test Number 392 input
pwd
#Test Number 393 input
cd /
#Test Number 394 input
pwd

#Test Number 395 input
pwd
#Test Number 396 input
cd '/////'
#Test Number 397 input
pwd

#Test Number 398 input
pwd
#Test Number 399 input
cd "$PWD/file_tests"
#Test Number 400 input
pwd

#Test Number 401 input
cd '/////' 2>/dev/null

#Test Number 402 input
cd '/etc' 

#Test Number 403 input
cd '/var' 

#Test Number 404 input
cd "doesntexist" 2>/dev/null 

#Test Number 405 input
cd ../../..

#Test Number 406 input
cd "wtf" 2>/dev/null 

#Test Number 407 input
cd ?

#Test Number 408 input
cd +

#Test Number 409 input
cd _

#Test Number 410 input
cd woof

#Test Number 411 input
cd bark bark

#Test Number 412 input
cd '/' 

#Test Number 413 input
pwd
#Test Number 414 input
cd "doesntexist"
#Test Number 415 input
pwd

#Test Number 416 input
pwd
#Test Number 417 input
cd "doesntexist"
#Test Number 418 input
pwd

#Test Number 419 input
pwd
#Test Number 420 input
cd ../../..
#Test Number 421 input
pwd

#Test Number 422 input
pwd
#Test Number 423 input
cd "wtf"
#Test Number 424 input
pwd

#Test Number 425 input
pwd
#Test Number 426 input
cd ..
#Test Number 427 input
cd ..
#Test Number 428 input
pwd

#Test Number 429 input
pwd
#Test Number 430 input
cd ?
#Test Number 431 input
pwd

#Test Number 432 input
pwd
#Test Number 433 input
cd +
#Test Number 434 input
pwd

#Test Number 435 input
pwd
#Test Number 436 input
cd _
#Test Number 437 input
pwd

#Test Number 438 input
cd ../../
#Test Number 439 input
cd -
#Test Number 440 input
cd -

#Test Number 441 input
pwd
#Test Number 442 input
cd echo
#Test Number 443 input
pwd

#Test Number 444 input
pwd
#Test Number 445 input
cd echo echo
#Test Number 446 input
pwd

#Test Number 447 input
pwd
#Test Number 448 input
cd '/'
#Test Number 449 input
pwd

#Test Number 450 input
pwd
#Test Number 451 input
cd $PWD/file_tests
#Test Number 452 input
pwd

#Test Number 453 input
pwd
#Test Number 454 input
cd $OLDPWD/something
#Test Number 455 input
pwd

#Test Number 456 input
pwd
#Test Number 457 input
cd ~
#Test Number 458 input
cd - ananas dot jpeg
#Test Number 459 input
pwd

# might need to change the directory by yourself, that supposed to be valid =)
#Test Number 460 input
pwd
#Test Number 461 input
cd includes/ djhwbdhwbd wgdyuhgw jdwjdh wuiydjwh 
#Test Number 462 input
pwd

#Test Number 463 input
pwd
#Test Number 464 input
cd ~ asd w dd q asd
#Test Number 465 input
pwd

#Test Number 466 input
pwd
#Test Number 467 input
cd ~
#Test Number 468 input
cd -
#Test Number 469 input
pwd

#Test Number 470 input
pwd
#Test Number 471 input
cd -
#Test Number 472 input
pwd

#Test Number 473 input
pwd
#Test Number 474 input
cd ~
#Test Number 475 input
pwd

# might need to change the directory by yourself, that supposed to be valid =)
#Test Number 476 input
pwd
#Test Number 477 input
cd ../libft
#Test Number 478 input
pwd

# might need to change the directory by yourself, that supposed to be valid =)
#Test Number 479 input
pwd
#Test Number 480 input
cd ../libft ojid iowjiojwoid joijd owjoid jwojd 
#Test Number 481 input
pwd

### ENV ###
#Test Number 482 input
env | grep DOESNT_EXIST

#Test Number 483 input
env | grep HOME

#Test Number 484 input
env | grep USER

#Test Number 485 input
env | wc -l

#Test Number 486 input
env what

### PWD ###
#Test Number 487 input
pwd

#Test Number 488 input
"pwd"

#Test Number 489 input
pwd test42

#Test Number 490 input
pwd 42 42 42

#Test Number 491 input
pwd pwd

#Test Number 492 input
pwd pwd pwd

### EXPORT ###
#Test Number 493 input
/bin/echo $HALLO42
#Test Number 494 input
env | grep HALLO42
#Test Number 495 input
export HALLO42=42
#Test Number 496 input
/bin/echo $HALLO42
#Test Number 497 input
env | grep HALLO42

#Test Number 498 input
/bin/echo $HOME
#Test Number 499 input
env | grep HOME
#Test Number 500 input
export HOME=42
#Test Number 501 input
/bin/echo $HOME
#Test Number 502 input
env | grep HOME

#Test Number 503 input
export =============123

#Test Number 504 input
export

#Test Number 505 input
export =

#Test Number 506 input
export =42

#Test Number 507 input
export ''=''

#Test Number 508 input
export ""=""

#Test Number 509 input
export export

#Test Number 510 input
export echo

#Test Number 511 input
export cd

#Test Number 512 input
export test

#Test Number 513 input
export TEST

#Test Number 514 input
export $? 

#Test Number 515 input
export TEST

#Test Number 516 input
export TEST=

#Test Number 517 input
export TEST=123

#Test Number 518 input
export ___TEST=123

#Test Number 519 input
export --TEST=123

#Test Number 520 input
export ''=''

#Test Number 521 input
export "="="="

#Test Number 522 input
export '='='='

#Test Number 523 input
export TE-ST=100

#Test Number 524 input
export -TEST=100

#Test Number 525 input
export TEST-=100

#Test Number 526 input
export _TEST=100

#Test Number 527 input
export ==========

#Test Number 528 input
export 1TEST=

#Test Number 529 input
export ""=""

#Test Number 530 input
export TES=T=""

#Test Number 531 input
export TE+S=T=""

#Test Number 532 input
export TES.T=123

#Test Number 533 input
export TES.T=123

#Test Number 534 input
export TES+T=123

#Test Number 535 input
export TES=T=123

#Test Number 536 input
export TES}T=123

#Test Number 537 input
export TES{T=123

#Test Number 538 input
export TES-T=123

#Test Number 539 input
export -TEST=123

#Test Number 540 input
export _TEST=123

#Test Number 541 input
export TES_T=123

#Test Number 542 input
export TEST_=123

#Test Number 543 input
export TE*ST=123

#Test Number 544 input
export TES#T=123

#Test Number 545 input
export TES@T=123

#Test Number 546 input
export TES!T=123

#Test Number 547 input
export TES$?T=123

#Test Number 548 input
export =============123

#Test Number 549 input
export +++++++=123

#Test Number 550 input
export ________=123

#Test Number 551 input
export TES^T=123

#Test Number 552 input
export TES!T=123

#Test Number 553 input
export TES\~T=123

#Test Number 554 input
export TEST+=100

#Test Number 555 input
export TES_T=123
#Test Number 556 input
/bin/echo $TES_T
#Test Number 557 input
env | grep TES_T

#Test Number 558 input
export HELLO42=T=""
#Test Number 559 input
/bin/echo $HELLO42
#Test Number 560 input
env | grep HELLO42
#Test Number 561 input
env | grep HELLO42=T=

#Test Number 562 input
echo $?
#Test Number 563 input
export ?=hallo
#Test Number 564 input
echo $?

#Test Number 565 input
/bin/echo $test
#Test Number 566 input
export test=42 | echo 99
#Test Number 567 input
/bin/echo $test

#Test Number 568 input
/bin/echo $mini_test
#Test Number 569 input
env | grep mini_test
#Test Number 570 input
export mini_test=
#Test Number 571 input
/bin/echo $mini_test
#Test Number 572 input
env | grep mini_test

### UNSET ###
#Test Number 573 input
unset

#Test Number 574 input
unset ""

#Test Number 575 input
unset =

#Test Number 576 input
unset "="

#Test Number 577 input
unset ""=

#Test Number 578 input
unset =""

#Test Number 579 input
unset ==

#Test Number 580 input
unset ?

#Test Number 581 input
unset "?"

#Test Number 582 input
unset $

#Test Number 583 input
unset "$"

#Test Number 584 input
unset $""

#Test Number 585 input
export TEST=100

#Test Number 586 input
unset doesntexist

#Test Number 587 input
unset OLDPWD 

#Test Number 588 input
unset PATH 

#Test Number 589 input
unset PATH 

#Test Number 590 input
unset PATH 

#Test Number 591 input
unset TES;T

#Test Number 592 input
unset TES.T

#Test Number 593 input
unset TES+T

#Test Number 594 input
unset TES=T

#Test Number 595 input
unset TES}T

#Test Number 596 input
unset TES{T

#Test Number 597 input
unset TES-T

#Test Number 598 input
unset -TEST

#Test Number 599 input
unset _TEST

#Test Number 600 input
unset TES_T

#Test Number 601 input
unset TEST_

#Test Number 602 input
unset TE*ST

#Test Number 603 input
unset TES#T

#Test Number 604 input
unset TES@T

#Test Number 605 input
unset TES!T

#Test Number 606 input
unset TES$?T

#Test Number 607 input
unset ============

#Test Number 608 input
unset +++++++

#Test Number 609 input
unset ________

#Test Number 610 input
unset export

#Test Number 611 input
unset echo

#Test Number 612 input
unset pwd

#Test Number 613 input
unset cd

#Test Number 614 input
unset unset

#Test Number 615 input
unset sudo

#Test Number 616 input
unset TES^T

#Test Number 617 input
unset TES!T

#Test Number 618 input
unset TES\~T

#Test Number 619 input
/bin/echo $HOME
#Test Number 620 input
unset $HOME
#Test Number 621 input
/bin/echo $HOME

#Test Number 622 input
/bin/echo $HOME
#Test Number 623 input
unset HOME
#Test Number 624 input
/bin/echo $HOME

#Test Number 625 input
/bin/echo $HOME
#Test Number 626 input
unset HOME
#Test Number 627 input
unset HOME
#Test Number 628 input
unset HOME
#Test Number 629 input
/bin/echo $HOME

#Test Number 630 input
/bin/echo $HOME
#Test Number 631 input
unset HOME
#Test Number 632 input
unset HOME
#Test Number 633 input
unset HOME
#Test Number 634 input
unset HOME
#Test Number 635 input
/bin/echo $HOME

###  EXIT ###

#Test Number 636 input
exit 9223372036854775807

#Test Number 637 input
exit something somethingv2

#Test Number 638 input
exit 0 0

#Test Number 639 input
exit

#Test Number 640 input
exit ""

#Test Number 641 input
exit "+100"

#Test Number 642 input
exit "-100"

#Test Number 643 input
exit -9223372036854775805

#Test Number 644 input
exit 0

#Test Number 645 input
exit 10

#Test Number 646 input
exit 42

#Test Number 647 input
exit 1

#Test Number 648 input
exit +++++

#Test Number 649 input
exit ++++++

#Test Number 650 input
exit +1

#Test Number 651 input
exit ++1

#Test Number 652 input
exit ++12560

#Test Number 653 input
exit -----

#Test Number 654 input
exit ------

#Test Number 655 input
exit -1

#Test Number 656 input
exit --1

#Test Number 657 input
exit -12560

#Test Number 658 input
exit --12560

#Test Number 659 input
exit 255

#Test Number 660 input
exit 1 2

#Test Number 661 input
exit 1 2 3

#Test Number 662 input
exit A

#Test Number 663 input
exit A 2 3

#Test Number 664 input
exit "A"

#Test Number 665 input
exit "+++"

#Test Number 666 input
exit ++++3193912939

#Test Number 667 input
exit 01

#Test Number 668 input
exit 001

#Test Number 669 input
exit 0001

#Test Number 670 input
exit +++000

#Test Number 671 input
exit ++++000

#Test Number 672 input
exit ---000

#Test Number 673 input
exit ----000

#Test Number 674 input
exit "something"

#Test Number 675 input
exit x

#Test Number 676 input
exit echo

#Test Number 677 input
exit cd ..

#Test Number 678 input
exit exit

#Test Number 679 input
exit 42 42 42 42 42 
