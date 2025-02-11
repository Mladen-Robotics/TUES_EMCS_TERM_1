from machine import Pin,ADC
import time

pot = ADC(Pin(26))

DIGIT_PORT_NUMBERS = { 
  'A':15,'B':14,'C':9,'D':10,'E':11,'F':13,'G':12, 'DP' : 27
}

DIGIT_PORTS = {}

BAR_PINS = [
  28,8,7, 6, 5, 4, 3, 2, 1, 0
]

BAR = []

DIGITS = {
  0: 'ABCDEF',
  1: 'EF',
  2: 'ABGED',
  3: 'ABGCD',
  4: 'FBGC',
  5: 'AFGCD',
  6: 'AFGEDC',
  7: 'ABC',
  8: 'ABCDEFG',
  9: 'ABCDGF',
}

def init_bar_pins():
  for i in BAR_PINS:
    BAR.append(Pin(i, Pin.OUT))

def init_digit_ports():
  for letter, port in DIGIT_PORT_NUMBERS.items():
    DIGIT_PORTS[letter] = Pin(port, Pin.OUT)

def display_digit(n):
  digit_code = DIGITS[n]
  for i in DIGIT_PORTS.values():
    i.value(0)
  for i in BAR:
    i.value(0)
  if n == 9:
    DIGIT_PORTS['DP'].value(1)
  for i in digit_code:
    DIGIT_PORTS[i].value(1)
  
  for i in range(n):
    BAR[i].value(1)

try:
  init_digit_ports()
  init_bar_pins()
#   print(BAR)
#   print(DIGIT_PORTS)
  
  # for i in range(0,10):
  #   display_digit(i)
  #   time.sleep(1)
  BAR[0].value(1)
  while True:
    pot_val = pot.read_u16()
    
    digit = int(pot_val / 7281)
    # print(str(int(digit)), ' ' + str(digit))
    display_digit(digit)
    time.sleep(0.1)
except KeyboardInterrupt:
  print("Exit")

# while True:
#   value = pot.read_u16()
#   print("Pot value:",str(value))
#   time.sleep(0.1)

