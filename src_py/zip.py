import os, sys

def my_zip(range1, range2):

    min = len(range1)

    
    if len(range2) < len(range1): 
        min = len(range2)
   
    res = []
    
    for i in range(0, min):
        res.append((range1[i], range2[i]))

    return res



def std_zip(range1, range2):
    res = []
    for pair in zip(range1, range2):
        res.append((pair[0], pair[1]))
    return res

print(my_zip([1, 5, 3, 8, 35], [2, 7, 9]))
print(std_zip([1, 5, 3, 8, 35], [2, 7, 9]))


def final_balance(init_sum, interest_rate, years, round_num = 2):

    # s1 = s0 + (s0 / 100 * interest_rate) = s0 * ( 1 + interest / 100)
    # s1 = s0 * ( 1 + interest / 100)
    # s2 = s1 * (1 + int / 100)
    # s2 = s0 * (1 + int/100) * (1 + int/100) -> s0 * (1 + int/100) ** years

    return round(init_sum * (1 + interest_rate / 100) ** years, round_num)

print(final_balance(700, 7, 10))

def math_task(data):
    answer = []
    for elem in data:
        answer.append(elem ** 3)
    for i in range(len(answer)):
        answer[i] = answer[i] % 7
    for i in range(len(answer)):
        answer[i] = answer[i] + data[i]
    return answer

print(math_task([1,2,3,4]))

def reversed_(array):
    array1 = array.copy()
    rv = []
    while array1:
        rv.append(array1.pop())
    return rv
if reversed_(reversed_([1, 2, 3])) == [1, 2, 3]:
    print("Все хорошо")
else:
    raise RuntimeError("Ошибка, после обращения дважды не получается исходный массив!")

arr = [1, 2, 3]
if reversed_(reversed_(arr)) == arr:
    print("Все хорошо")
else:
    raise RuntimeError("Ошибка, после обращения дважды не получается исходный массив!")


def fifth_element(some_list: list) -> list:
    return some_list[-5::-5]

print(fifth_element(['e',6,8,'A','>','^','S','$','R','C',6,'+','#',9,'/',1,'T','!','%','K',7,'-','O','*','<',2,'h',4,'g']))

def process_string(string):
    return string[1:].lower().replace('intern', 'junior')

print(process_string('IIntern reads a lot of books'))

def check_string(string):
    # 1. Check for extra spaces on the left or right
    if string != string.strip():
        print("[" + string + "]: False")
        return False

    # 2. The last character must be a dot
    if not string.endswith('.'):
        print("[" + string + "]: False")
        return False

    # Remove the dot to check the words
    words = string[:-1].split()

    if not words:
        print("[" + string + "]: False")
        return False

    # 3. The first word must start with a capital letter
    if not words[0][0].isupper() or not words[0][1:].islower():
        return False

    # 4. All other words must be lowercase
    for word in words[1:]:
        if not word.islower():
            print("[" + string + "]: False")
            return False

    print("[" + string + "]: OK")
    return True


check_string("Hello world.")        # True
check_string("Hello World.")        # False
check_string(" hello world.")       # False
check_string("Hello world")         # False
check_string("Hello world .")       # False
check_string("Hello world again.")  # True

