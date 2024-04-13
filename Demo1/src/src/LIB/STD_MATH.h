/*
 * STD_MATH.h
 *
 * Created: 11/25/2023 6:25:41 PM
 *  Author: iT-User
 */ 


#ifndef STD_MATH_H_
#define STD_MATH_H_



// Set bit BIT in REG
#define SET_BIT(REG, BIT)  (REG) |= (1 << (BIT))
// Clear bit BIT in REG
#define CLR_BIT(REG, BIT)  ((REG) &= ~(1 << (BIT)))
// Toggle bit BIT in REG
#define TGL_BIT(REG, BIT)   ((REG) ^= (1 << (BIT)))
// Get bit BIT in REG
#define GET_BIT(REG, BIT)   (((REG) >> (BIT)) & 1)

// Set high nibble in REG
#define SET_HIGH_NIB(REG) ((REG) |= 0xF0)
// Clear high nibble in REG
#define CLR_HIGH_NIB(REG)  ((REG) &= 0x0F)
// Toggle high nibble in REG
#define TGL_HIGH_NIB(REG)  ((REG) ^= 0xF0)
// Get high nibble in REG
#define GET_HIGH_NIB(REG)  (((REG) & 0xF0) >> 4)

// Set low nibble in REG
#define SET_LOW_NIB(REG)   ((REG) |= 0x0F)
// Clear low nibble in REG
#define CLR_LOW_NIB(REG)   ((REG) &= 0xF0)
// Toggle low nibble in REG
#define TGL_LOW_NIB(REG)   ((REG) ^= 0x0F)
// Get low nibble in REG
#define GET_LOW_NIB(REG)   ((REG) & 0x0F)

// Assign VALUE to REG
#define ASSIGN_REG(REG, VALUE) ((REG) = (((REG) & 0x00) | (VALUE)))
// Assign VALUE to high nibble REG
#define ASSIGN_HIGH_NIB(REG, VALUE) ((REG) = (((REG) & 0x0F) | ((VALUE) << 4)))
// Assign VALUE to low nibble REG
#define ASSIGN_LOW_NIB(REG, VALUE)  ((REG) = (((REG) & 0xF0) | (VALUE)))

//setting the whole Register
#define SET_REG(REG) ((REG) = (((REG) | 0xFF)))
//clearing the whole register
#define CLR_REG(REG) ((REG) = (((REG) & 0x00)))

// Right shift by NO in REG
#define RSHFT_REG(REG, NO)  ((REG) = ((REG) >> (NO)))
// Left shift by NO in REG
#define LSHFT_REG(REG, NO)  ((REG) = ((REG) << (NO)))
// Circular right shift by NO in REG
#define CRSHFT_REG(REG, NO) (REG=((REG) << (8*sizeof(REG) - (NO))) | ((REG) >> (NO)))
// Circular left shift by NO in REG
#define CLSHFT_REG(REG, NO)  (REG=((REG) >> (8*sizeof(REG) - (NO))) | ((REG) << (NO)))

//CONCATENATING THE PINS INTO THE REGISTER
#define CONCAT(b0,b1,b2,b3,b4,b5,b6,b7)         CONCAT_HELPER(b0,b1,b2,b3,b4,b5,b6,b7)  
#define CONCAT_HELPER(p0,p1,p2,p3,p4,p5,p6,p7)		0b##p7##p6##p5##p4##p3##p2##p1##p0



#endif /* STD_MATH_H_ */