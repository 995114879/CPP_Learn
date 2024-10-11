package main

import (
	"fmt"
)

func main() {
	c1 := complex(1, 2)
	c2 := complex(2, 3)
	c3 := c1 + c2
	fmt.Printf("%v\n", c3)
}