---
layout: lecture
pretty_table: true
order: 2
title: Data Science with Python and Pandas
mermaid:
  enabled: true
  zoomable: true
code_diff: true
map: true
chart:
  chartjs: true
  echarts: true
  vega_lite: true
tikzjax: true
typograms: true
toc:
  - name: 1. Overview
  - name: 2. Processing data from a file
  - name: 3. Dates and Time
  - name: 4. Processing JSON data
  - name: 5. Reading data from a file using Pandas
  - name: 6. Extracting row and columns
  - name: 7. Data Aggregation using Pandas
  - name: 8. Joining Pandas Dataframes
  - name: 9. Wide and long data formats
  - name: 10. Data visualisation using Matplotlib
  - name: 11. Accessing SQLite Databases
---

## 1. Overview

{% details Abstract: Workshop Description %}

This workshop covers reusable Python, file and JSON processing, dates and times,
and data analysis with Pandas, Matplotlib, and SQLite. It continues from the
introductory Python workshop and uses materials from
[Data Carpentry](https://datacarpentry.org/)'s
[Data Analysis and Visualization with Python for Social Scientists](https://datacarpentry.github.io/python-socialsci/)
lesson, starting at Episode 4 (Creating re-usable code).

Link to workshop page: [https://linhbngo.github.io/csc-workshops/python-pandas/](https://linhbngo.github.io/csc-workshops/python-pandas/)

{% enddetails %}

{% details note Data Preparation %}

- You will specify the followings for requesting resources:
    - `--ntasks-per-node=10 --mem=16G`

- Run the following inside a cell to download the data files used in this workshop.

```bash
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SAFI_clean.csv
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SAFI_results.csv
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SAFI_full_shortname.csv
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SAFI.json
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SN7577.tab
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SN7577i_a.csv
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SN7577i_aa.csv
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SN7577i_b.csv
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SN7577i_bb.csv
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SN7577i_c.csv
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SN7577i_d.csv
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/SN7577.sqlite
!wget -q https://raw.githubusercontent.com/datacarpentry/python-socialsci/gh-pages/data/Newspapers.csv
!ls -lh
```

- Keep the data files in the same folder as the notebook (Colab's `/content` directory by default).

{% enddetails %}


## 2. Processing data from a file

{% details Questions %}

- How can I read and write files?
- What kind of data files can I read?

{% enddetails %}

{% details Objectives %}

- Describe a file handle
- Use `with open() as` to open files for reading and auto-close files
- Create and open for writing or appending and auto-close files
- Explain what is meant by a record

{% enddetails %}

{% details note Reading and Writing datasets %}

In all of our examples so far, we have directly allocated values to variables in the code we have written before using the variables.

Python has an `input()` function which will ask for input from the user, but for any large amounts of data this will be an impractical way of collecting data.

The reality is that most of the data that your program uses will be read from a file. Additionally, apart from when you are developing, most of your program output will be written to a file.

In this episode we will look at how to read and write files of data in Python.

There are in fact many different approaches to reading data files and which one you choose will depend on such things as the size of the file and the data format of the file.

In this episode we will;

- We will read a file which is in .csv (Comma Separated Values) format.
- We will use standard core Python functions to do this
- We will read the file one line at a time ( line = record = row of a table)
- We will perform simple processing of the file data and print the output
- We will split the file into smaller files based on some processing

The file we will be using is only a small file (131 data records), but the approach we are using will work for any size of file. Imagine 131M records. This is because we only process one record at a time so the memory requirements of the programs will be very small. The larger the file the more the processing time required.

Other approaches to reading files will typically expect to read the whole file in one go. This can be efficient when you subsequently process the data but it require large amounts of memory to hold the entire file. We will look at this approach later when the look at the Pandas package.

For our examples in this episode we are going to use the SAFI_results.csv file. This is available from the [lesson data directory](https://github.com/datacarpentry/python-socialsci/tree/gh-pages/data).

The code assumes that the file is in the same directory as your notebook.

We will build up our programs in simple steps.

```python
with open("SAFI_results.csv") as f:       # Open the file and assign it to a new variable which we call 'f'.
                                          # The file will be read-only by default.
                                          # As long as the following code is indented, the file 'f' will be open.
    for line in f:                        # We use a for loop to iterate through the file one line at a time.
        print(line)                       # We simply print the line.
        
print("I'm on to something else now.")    # When we are finished with this file, we stop indenting the code and the file is closed automatically.
```

```output
Column1,A01_interview_date,A03_quest_no,A04_start,A05_end,A06_province,A07_district,A08_ward,A09_village,A11_years_farm,A12_agr_assoc,B11_remittance_money,B16_years_liv,B17_parents_liv,B18_sp_parents_liv,B19_grand_liv,B20_sp_grand_liv,B_no_membrs,C01_respondent_roof_type,C02_respondent_wall_type,C02_respondent_wall_type_other,C03_respondent_floor_type,C04_window_type,C05_buildings_in_compound,C06_rooms,C07_other_buildings,D_plots_count,E01_water_use,E17_no_enough_water,E19_period_use,E20_exper_other,E21_other_meth,E23_memb_assoc,E24_resp_assoc,E25_fees_water,E26_affect_conflicts,E_no_group_count,E_yes_group_count,F04_need_money,F05_money_source_other,F06_crops_contr,F08_emply_lab,F09_du_labour,F10_liv_owned_other,F12_poultry,F13_du_look_aftr_cows,F_liv_count,G01_no_meals,_members_count,_note,gps:Accuracy,gps:Altitude,gps:Latitude,gps:Longitude,instanceID

0,17/11/2016,1,2017-03-23T09:49:57.000Z,2017-04-02T17:29:08.000Z,Province1,District1,Ward2,Village2,11,no,no,4,no,yes,no,yes,3,grass,muddaub,,earth,no,1,1,no,2,no,,,,,,,,,2,,,,,no,no,,yes,no,1,2,3,,14,698,-19.11225943,33.48345609,uuid:ec241f2c-0609-46ed-b5e8-fe575f6cefef
...
```

You can think of the file as being a list of strings. Each string in the list is one complete line from the file.

If you look at the output, you can see that the first record in the file is a header record containing column names. When we read a file in this way, the column headings have no significance, the computer sees them as another record in the file.

{% enddetails %}

{% details note Step 2 - Select a specific ‘column’ from the records in the file %}

We know that the first record in the file is a header record and we want to ignore it. To do this we call the `readline()` method of the file handle f. We don’t need to assign the line that it will return to a variable as we are not going to use it.

As we read the file the line variable is a string containing a complete record. The fields or columns of the record are separated by each other by “,” as it is a csv file.

As line is a string we can use the `split()` method to convert it to a list of column values. We are specicically going to select the column which is the 19th entry in the list (remember the list index starts at 0). This refers to the C01_respondent_roof_type column. We are going to examine the different roof types.

```python
with open ("SAFI_results.csv") as f:  # Open the file and assign it to a variable called 'f'.
                                      # Indent the code to keep the file open. Stop indenting to close.
    f.readline()                      # First line is a header so ignore it.

    for line in f:
        print(line.split(",")[18])    # Index 18, the 19th column is C01_respondent_roof_type.
```

```output
grass
grass
mabatisloping
mabatisloping
grass
grass
grass
mabatisloping
...
```

Having a list of the roof types from all of the records is one thing, but it is more likely that we would want a count of each type. By scanning up and down the previous output, there appear to be 3 different types, but we will play safe and assume there may be more.

```python
# 1
with open ("SAFI_results.csv") as f:

# 2
    f.readline()

# 3
    grass_roof = 0
    mabatisloping_roof = 0
    mabatipitched_roof = 0
    roof_type_other = 0

    for line in f:
# 4
        roof_type = line.split(",")[18]
# 5    
        if roof_type == 'grass' :
            grass_roof += 1
        elif roof_type == 'mabatisloping' :
            mabatisloping_roof += 1
        elif roof_type == 'mabatipitched' :
            mabatipitched_roof += 1
        else :
            roof_type_other += 1

#6
print("There are ", grass_roof, " grass roofs")
print("There are ", mabatisloping_roof, " mabatisloping roofs")
print("There are ", mabatipitched_roof, " mabatipitchedg roofs")
print("There are ", roof_type_other, " other roof types")
```

```output
There are 73 grass roofs
There are 48 mabatisloping roofs
There are 10 mabatipitchedg roofs
There are 0 other roof types
```

What are we doing here?

1. Open the file
2. Ignore the headerline
3. Initialise roof type variables to 0
4. Extract the C01_respondent_roof_type information from each record
5. Increment the appropriate variable
6. Print out the results (we have stopped indenting so the file will be closed)

Instead of printing out the counts of the roof types, you may want to extract all of one particular roof type to a separate file. Let us assume we want all of the grass roof records to be written to a file.

```python
# 1
with open ("SAFI_results.csv") as fr:              # Note how we have used a new variable name, 'fr'.
                                                   # The file is read-only by default.

    with open ("SAFI_grass_roof.csv", "w") as fw:  # We are keeping 'fr' open so we indent.
                                                   # We specify a second parameter, "w" to make this file writeable.
                                                   # We use a different variable, 'fw'.
        for line in fr:
# 2    
            if line.split(",")[18] == 'grass' :
                fw.write(line)
```

What are we doing here?

1. Open the files. Because there are now two files, each has its own file handle: `fr` for the file we read and `fw` for the file we are going to write. (They are just variable names so you can use anything you like). For the file we are going to write to we use `w` for the second parameter. If the file does not exist it will be created. If it does exist, then the contents will be overwritten. If we want to append to an existing file we can use `a` as the second parameter.
2. Because we are just testing a specific field from the record to have a certain value, we don’t need to put it into a variable first. If the expression is True, then we use `write()` method to write the complete line just as we read it to the output file.

In this example we didn’t bother skipping the header line as it would fail the test in the if statement. If we did want to include it we could have added the line

```python
fw.write(fr.readline())
```

before the for loop

{% details Challenge: Exercise %}

From the SAFI_results.csv file extract all of the records where the `C01_respondent_roof_type` (index 18) has a value of `'grass'` and the `C02_respondent_wall_type` (index 19) has a value of `'muddaub'` and write them to a file. Within the same program write all of the records where `C01_respondent_roof_type` (index 18) has a value of `'grass'` and the `C02_respondent_wall_type` (index 19) has a value of `'burntbricks'` and write them to a separate file. In both files include the header record.

```python
with open ("SAFI_results.csv") as fr:

   with open ("SAFI_grass_roof_muddaub.csv", "w") as fw1:
      with open ("SAFI_grass_roof_burntbricks.csv", "w") as fw2:

          headerline = fr.readline()
          fw1.write(headerline)
          fw2.write(headerline)

          for line in fr:
              if line.split(",")[18] == 'grass' :
                  if line.split(",")[19] == 'muddaub' :
                      fw1.write(line)
                  if line.split(",")[19] == 'burntbricks' :
                      fw2.write(line)    
```

In our example of printing the counts for the roof types, we assumed that we knew what the likely roof types were. Although we did have an `'other'` option to catch anything we missed. Had there been any we would still be non the wiser as to what they represented. We were able to decide on the specific roof types by manually scanning the list of `C01_respondent_roof_type` values. This was only practical because of the small file size. For a multi-million record file we could not have done this.

We would like a way of creating a list of the different roof types and at the same time counting them. We can do this by using not a Python list structure, but a Python dictionary.

{% enddetails %}

{% enddetails %}

{% details note The Python dictionary structure %}

In Python a dictionary object maps keys to values. A dictionary can hold any number of keys and values but a key cannot be duplicated.

The following code shows examples of creating a dictionary object and manipulating keys and values.

```python
# an empty dictionary
myDict = {}

# A dictionary with a single Key-value pair

personDict = {'Name' : 'Peter'}

# I can add more about 'Peter' to the dictionary

personDict['Location'] = 'Manchester'

# I can print all of the keys and values from the dictionary

print(personDict.items())

# I can print all of the keys and values from the dictionary - and make it look a bit nicer

for item in personDict:
    print(item, "=", personDict[item])

# or all of the keys

print(personDict.keys())

# or all of the values

print(personDict.values())

# I can access the value for a given key

x = personDict['Name']
print(x)

# I can change value for a given key

personDict['Name'] = "Fred"
print(personDict['Name'])

# I can check if a key exists

key = 'Name'

if key in personDict :
    print("already exists")
else :
    personDict[key] = "New value"
```

```output
dict_items([('Location', 'Manchester'), ('Name', 'Peter')])
Location = Manchester
Name = Peter
dict_keys(['Location', 'Name'])
dict_values(['Manchester', 'Peter'])
Peter
Fred
already exists
```

{% details Challenge: Exercise %}

1. Create a dictionary called `dict_roof_types` with initial keys of `type1` and `type2` and give them values of 1 and 3.
2. Add a third key `type3` with a value of 6.
3. Add code to check if a key of `type4` exists. If it does not add it to the dictionary with a value of 1 if it does, increment its value by 1
4. Add code to check if a key of `type2` exists. If it does not add it to the dictionary with a value of 1 if it does, increment its value by 1
5. Print out all of the keys and values from the dictionary

```python

# 1
dict_roof_types = {'type1' : 1 , 'type2' : 3}

# 2
dict_roof_types['type3'] = 6

# 3
key = 'type4'
if key in dict_roof_types :
    dict_roof_types[key] += 1
else :
    dict_roof_types[key] = 1

# 4
key = 'type2'
if key in dict_roof_types :
    dict_roof_types[key] += 1
else :
    dict_roof_types[key] = 1
 
# 5
for item in dict_roof_types:
    print(item, "=", dict_roof_types[item])
    
```

We are now in a position to re-write our count of roof types example without knowing in advance what any of the roof types are.

```python
# 1
with open ("SAFI_results.csv") as f:

# 2
    f.readline()

# 3
    dict_roof_types = {}

    for line in f:
# 4
        roof_type = line.split(",")[18]
# 5    
        if roof_type in dict_roof_types :
            dict_roof_types[roof_type] += 1
        else :
            dict_roof_types[roof_type] = 1

# 6

for item in dict_roof_types:
    print(item, "=", dict_roof_types[item])
```

```output
grass = 73
mabatisloping = 48
mabatipitched = 10
```

What are we doing here?

1. Open the file
2. Ignore the headerline
3. Create an empty dictionary
4. Extract the C01_respondent_roof_type information from each record
5. Either add to the dictionary with a value of 1 or increment the current value for the key by 1
6. Print out the contents of the dictionary (stopped indenting so file is closed)

You can apply the same approach to count values in any of the fields/columns of the file.

{% enddetails %}

{% enddetails %}

{% details Key Points %}

- Reading data from files is far more common than program ‘input’ requests or hard coding values
- Python provides simple means of reading from a text file and writing to a text file
- Tabular data is commonly recorded in a ‘csv’ file
- Text files like csv files can be thought of as being a list of strings. Each string is a complete record
- You can read and write a file one record at a time
- Python has builtin functions to parse (split up) records into individual tokens

{% enddetails %}


## 3. Dates and Time

{% details Questions %}

- How are dates and time represented in Python?
- How can I manipulate dates and times?

{% enddetails %}

{% details Objectives %}

- Describe some of the datetime functions available in Python
- Describe the use of format strings to describe the layout of a date and/or time string
- Make use of date arithmetic

{% enddetails %}

{% details note Date and Times in Python %}

Python can be very flexible in how it interprets ‘strings’ which you want to be considered as a date, time, or date and time, but you have to tell Python how the various parts of the date and/or time are represented in your ‘string’. You can do this by creating a `format`. In a `format`, different case sensitive characters preceded by the `%` character act as placeholders for parts of the date/time, for example `%Y` represents year formatted as 4 digit number such as 2014.

A full list of the characters used and what they represent can be found towards the end of the datetime section of the official Python documentation.

There is a `today()` method which allows you to get the current date and time. By default it is displayed in a format similar to the ISO 8601 standard format.

To use the date and time functions you need to import the `datetime` module.

```python
from datetime import datetime

today = datetime.today()
print('ISO     :', today)
```

```output
ISO     : 2018-04-12 16:19:17.177441
```

We can use our own formatting instead. For example, if we wanted words instead of number and the 4 digit year at the end we could use the following.

```python
format = "%a %b %d %H:%M:%S %Y"

today_str = today.strftime(format)
print('strftime:', today_str)
print(type(today_str))

today_date = datetime.strptime(today_str, format)
print('strptime:', today_date.strftime(format))
print(type(today_date))
```

```output
strftime: Thu Apr 12 16:19:17 2018
<class 'str'>
strptime: Thu Apr 12 16:19:17 2018
<class 'datetime.datetime'>
```

`strftime` converts a datetime object to a string and `strptime` creates a datetime object from a string. When you print them using the same format string, they look the same.

The format of the date fields in the SAFI_results.csv file have been generated automatically to comform to the ISO 8601 standard.

When we read the file and extract the date fields, they are of type string. Before we can use them as dates, we need to convert them into Python date objects.

In the format string we use below, the `-` , `:` , `T` and `Z` characters are just that, characters in the string representing the date/time. Only the character preceded with `%` have special meanings.

Having converted the strings to datetime objects, there are a variety of methods that we can use to extract different components of the date/time.

```python
from datetime import datetime

format = "%Y-%m-%dT%H:%M:%S.%fZ"
f = open('SAFI_results.csv', 'r')

#skip the header line
line = f.readline()

# next line has data
line = f.readline()

strdate_start = line.split(',')[3]  # A04_start
strdate_end = line.split(',')[4]    # A05_end

print(type(strdate_start), strdate_start)
print(type(strdate_end), strdate_end)

# the full date and time
datetime_start = datetime.strptime(strdate_start, format)
print(type(datetime_start))
datetime_end = datetime.strptime(strdate_end, format)

print('formatted date and time', datetime_start)
print('formatted date and time', datetime_end)

# the date component
date_start = datetime.strptime(strdate_start, format).date()
print(type(date_start))
date_end = datetime.strptime(strdate_end, format).date()

print('formatted start date', date_start)
print('formatted end date', date_end)

# the time component
time_start = datetime.strptime(strdate_start, format).time()
print(type(time_start))
time_end = datetime.strptime(strdate_end, format).time()

print('formatted start time', time_start)
print('formatted end time', time_end)

f.close()
```

```output
<class 'str'> 2017-03-23T09:49:57.000Z
<class 'str'> 2017-04-02T17:29:08.000Z
<class 'datetime.datetime'>
formatted date and time 2017-03-23 09:49:57
formatted date and time 2017-04-02 17:29:08
<class 'datetime.date'>
formatted start date 2017-03-23
formatted end date 2017-04-02
<class 'datetime.time'>
formatted start time 09:49:57
formatted end time 17:29:08
```

{% enddetails %}

{% details note Components of dates and times %}

For a date or time we can also extract individual components of them. They are held internally in the datetime datastructure.

```python
# date parts.
print('formatted end date', date_end)
print(' end date year', date_end.year)
print(' end date month', date_end.month)
print(' end date day', date_end.day)
print (type(date_end.day))

# time parts.

print('formatted end time', time_end)
print(' end time hour', time_end.hour)
print(' end time minutes', time_end.minute)
print(' end time seconds', time_end.second)
print(type(time_end.second))
```

```output
formatted end date 2017-04-02
 end date year 2017
 end date month 4
 end date day 2
<class 'int'>
formatted end time 17:29:08
 end time hour 17
 end time minutes 29
 end time seconds 8
<class 'int'>
```

{% enddetails %}

{% details note Date arithmetic %}

We can also do arithmetic with the dates.

```python
date_diff = datetime_end - datetime_start
date_diff
print(type(datetime_start))
print(type(date_diff))
print(date_diff)

date_diff = datetime_start - datetime_end
print(type(date_diff))
print(date_diff)
```

```output
<class 'datetime.datetime'>
<class 'datetime.timedelta'>
10 days, 7:39:11
<class 'datetime.timedelta'>
-11 days, 16:20:49
```

{% details Challenge: Exercise %}

How do you interpret the last result?

The code below calculates the time difference between supposedly starting the survey and ending the survey (for each respondent).

```python
from datetime import datetime

format = "%Y-%m-%dT%H:%M:%S.%fZ"

f = open('SAFI_results.csv', 'r')

line = f.readline()

for line in f:
    #print(line)
    strdate_start = line.split(',')[3]
    strdate_end = line.split(',')[4]

    datetime_start = datetime.strptime(strdate_start, format)
    datetime_end = datetime.strptime(strdate_end, format)
    date_diff = datetime_end - datetime_start
    print(datetime_start, datetime_end, date_diff )

f.close()
```

```python
2017-03-23 09:49:57 2017-04-02 17:29:08 10 days, 7:39:11
2017-04-02 09:48:16 2017-04-02 17:26:19 7:38:03
2017-04-02 14:35:26 2017-04-02 17:26:53 2:51:27
2017-04-02 14:55:18 2017-04-02 17:27:16 2:31:58
2017-04-02 15:10:35 2017-04-02 17:27:35 2:17:00
2017-04-02 15:27:25 2017-04-02 17:28:02 2:00:37
2017-04-02 15:38:01 2017-04-02 17:28:19 1:50:18
2017-04-02 15:59:52 2017-04-02 17:28:39 1:28:47
2017-04-02 16:23:36 2017-04-02 16:42:08 0:18:32
...
```

{% enddetails %}

{% details Challenge: Exercise %}

1. In the `SAFI_results.csv` file the `A01_interview_date field` (index 1) contains a date in the form of ‘dd/mm/yyyy’. Read the file and calculate the differences in days (because the interview date is only given to the day) between the `A01_interview_date` values and the `A04_start` values. You will need to create a format string for the `A01_interview_date` field.
2. Looking at the results here and from the previous section of code. Do you think the use of the smartphone data entry system for the survey was being used in real time?

```python
from datetime import datetime

format1 = "%Y-%m-%dT%H:%M:%S.%fZ"
format2 = "%d/%m/%Y"

f = open('SAFI_results.csv', 'r')

line = f.readline()

for line in f:
    A01 = line.split(',')[1]
    A04 = line.split(',')[3]
   
    datetime_A04 = datetime.strptime(A04, format1)
    datetime_A01 = datetime.strptime(A01, format2)
    date_diff = datetime_A04 - datetime_A01
    print(datetime_A04, datetime_A01, date_diff.days )
     
f.close()
```

{% enddetails %}

{% enddetails %}

{% details Key Points %}

- Date and Time functions in Python come from the datetime library, which needs to be imported
- You can use format strings to have dates/times displayed in any representation you like
- Internally date and times are stored in special data structures which allow you to access the component parts of dates and times

{% enddetails %}


## 4. Processing JSON data

{% details Questions %}

- What is JSON format?
- How can I extract specific data items from a JSON record?
- How can I convert an array of JSON record into a table?

{% enddetails %}

{% details Objectives %}

- Describe the JSON data format
- Understand where JSON is typically used
- Appreciate some advantages of using JSON over tabular data
- Appreciate some dis-advantages of processing JSON documents
- Compare JSON to the Python Dict data type
- Use the JSON package to read a JSON file
- Display formatted JSON
- Select and display specific fields from a JSON document
- Write tabular data from selected elements from a JSON document to a csv file

{% enddetails %}

{% details note More on Dictionaries %}

In the Processing data from file episode we introduced the dictionary object.

We created dictionaries and we added `key : value` pairs to the dictionary.

In all of the examples that we used, the `value` was always a simple data type like an integer or a string.

The `value` associated with a `key` in a dictionary can be of any type including a `list` or even another `dictionary`.

We created a simple dictionary object with the following code:

```python
personDict = {'Name' : 'Peter'}
personDict['Location'] = 'Manchester'

print(personDict)
```

```python
{'Name': 'Peter', 'Location': 'Manchester'}
```

So far the keys in the dictionary each relate to a single piece of information about the person. What if we wanted to add a list of items?

```python
personDict['Children'] = ['John', 'Jane', 'Jack']
personDict['Children_count'] = 3
print(personDict)
```

```python
{'Name': 'Peter', 'Children': ['John', 'Jane', 'Jack'], 'Children_count': 3, 'Location': 'Manchester'}
```

Not only can I have a key where the value is a list, the value could also be another dictionary object. Suppose I want to add some telephone numbers

```python
personDict['phones'] = {'home' : '0102345678', 'mobile' : '07770123456'}
print(personDict.values())

# adding another phone
personDict['phones']['business'] =  '0161234234546'
print(personDict)
```

```python
dict_values(['Peter', ['John', 'Jane', 'Jack'], {'home': '0102345678', 'mobile': '07770123456'}, 3, 'Manchester'])
{'Name': 'Peter', 'Children': ['John', 'Jane', 'Jack'], 'phones': {'home': '0102345678', 'mobile': '07770123456', 'business': '0161234234546'}, 'Children_count': 3, 'Location': 'Manchester'}
```

{% details Challenge: Exercise %}

1. Using the personDict as a base add information relating to the persons home and work addresses including postcodes.
2. Print out the postcode for the work address.
3. Print out the names of the children on seperate lines (i.e. not as a list)

```python
personDict['Addresses'] = {'Home' : {'Addressline1' : '23 acacia ave.', 'Addressline2' : 'Romford', 'PostCode' : 'RO6 5WR'},
                          'Work' : {'Addressline1' : '19 Orford Road.', 'Addressline2' : 'London', 'PostCode' : 'EC4J 3XY'}
                          }

print(personDict['Addresses']['Work']['PostCode'])

for child in personDict['Children']:
    print(child)
    
```

The ability to create dictionaries containing lists and other dictionaries, makes the dictionary object very versatile, you can create an arbitrarily complex data structure of dictionaries within dictionaries.

In practice you will not be doing this manually, instead like most data you will read it in from a file.

{% enddetails %}

{% enddetails %}

{% details note The JSON data format %}

The JSON data format was designed as a way of allowing different machines or processes within machines to communicate with each other by sending messages constructed in a well defined format. JSON is now the preferred data format used by APIs (Application Programming Interfaces).

The JSON format although somewhat verbose is not only Human readable but it can also be mapped very easily to a Python dictionary object.

We are going to read a file of data formatted as JSON, convert it into a dictionary object in Python then selectively extract Key-Value pairs and create a csv file from the extracted data.

The JSON file we are going to use is the SAFI.json file. This is the output file from an electronic survey system called ODK. The JSON represents the answers to a series of survey questions. The questions themselves have been replaced with unique Keys, the values are the answers.

Because detailed surveys are by nature nested structures making it possible to record different levels of detail or selectively ask a set of specific questions based on the answer given a previous question, the structure of the answers for the survey can not only be complex and convoluted, it could easily be different from one survey respondent’s set of answers to another.

{% enddetails %}

{% details note Advantages of JSON %}

- Very popular data format for APIs (e.g. results from an Internet search)
- Human readable
- Each record (or document as they are called) is self contained. The equivalent of the column name and column values are in every record.
- Documents do not all have to have the same structure within the same file
- Document structures can be complex and nested

{% enddetails %}

{% details note Dis-advantages of JSON %}

- It is more verbose than the equivalent data in csv format
- Can be more difficult to process and display than csv formatted data

{% enddetails %}

{% details note Viewing JSON data %}

- JSON can often be viewed directly in the web browsers: example.
- Browser extensions are often available for ease of viewing JSON data e.g., Chrome, Firefox, Safari, etc.
- JSON files can be opened using text editors e.g., notepad, nano, textedit, etc.
- There are many websites which allow viewing or beautifying JSON data with ease. For example, http://jsonviewer.stack.hu/. Try pasting or loading JSON data in the second tab called “text” on that website and then clicking on the “format” button. Clicking on the first tab, “viewer” also gives another view of the data.

```python
import json

with open('SAFI.json') as json_data:
    d = json.load(json_data)
    print(type(d))
    print(type(d[0]))
    print(json.dumps(d[0], indent=2))
```

```output
<class 'list'>
<class 'dict'>
{
  "G02_months_lack_food": [
    "Jan"
  ],
  "G01_no_meals": 2,
  "E_no_group_count": "2",
  "A03_quest_no": "01",
...
```

Points to note:

1. We import the json package with an import statement.
2. We have chosen to use the `with` statement to open the SAFI.json file. Notice the `:` at the end of the line and the subsequent indentation. The `with` statement is in effect until we un-indent. At which time the file will automatically be closed. So we don’t need to do so explicitly.
3. ‘json_data’ is the file handle.
4. The `json.load` method is passed the file handle and reads the complete file.
5. The variable `d` is a list of dictionaries. (When we read the csv file we considered it to be a list of strings).
6. The `json.dumps` method can be used to print either the entire file or a specific dictionary from the list in a formatted manner by using the indent parameter)

By default the order in which the keys of the dictionary are printed is not guaranteed. If we want them in sorted order we can have them sorted by using the `sort_keys` parameter

```python
print(json.dumps(d[0], indent=2, sort_keys=True))
```

```python
{
  "A01_interview_date": "2016-11-17",
  "A03_quest_no": "01",
  "A04_start": "2017-03-23T09:49:57.000Z",
  "A05_end": "2017-04-02T17:29:08.000Z",
  "A06_province": "province1",
...
}
```

{% enddetails %}

{% details note Extracting specific fields from a JSON document %}

If we want to extract fields from a JSON document, the first step isto convert the JSON document into a Python dictionary. We have in fact already done this with the

```python
d = json.load(json_data)
```

line. `d` a list object and each entry in the list is a Dictionary object.

{% enddetails %}

{% details note Extract the fields we want into a flat format %}

Despite the arbitrary complexity of a JSON document or a Python dictionary object, we can adopt a very systematic approach to extracting individual fields form the structure.

The story so far: Our JSON file has been read into a variable `d`. We know that `d` is a list of dictionaries. Each dictionary represents a JSON document ( a record).

We can print the contents of the first dictionary in the list with

```python
print(json.dumps(d[0], indent=2, sort_keys=True))
```

{% details Challenge: Exercise %}

1. In the output from the code above there is a key with the name of `D_curr_crop`. Find it and by looking at the indentation and the `[` (lists) and `{` (dictionaries) describe in English how you could find the first occurrence of `D_curr_crop` starting with `d`.
2. Use a print statement to find out what it is.

{% details success Solution %}

- `d` is a list of dictionaries
- `d[0]` is the first dictionary
- within `d[0]` there is a key `D_plots` whose value is a list and contains dictionaries
- `d[0]['D_plots'][0]` is the first dictionary in the list
- within `d[0]['D_plots'][0]` there is a key `D_crops` which is also a list of dictionaries
- `d[0]['D_plots'][0]['D_crops'][0]` is the first dictionary in the list
- within this dictionary there is a key `D_curr_crop`

Being able to start at the outermost level and work your way in is very important when you need to extract specific items.

```python
print(d[0]['D_plots'][0]['D_crops'][0]['D_curr_crop'])
```

Being able to drill down in this way is very useful in helping you get a feel for the JSON data structure. In practice it is more likely that instead of returning the first occurrence of `D_curr_crop` you will want to return all of them. This requires a little more programming and to be aware of two potential problems.

1. `D_curr_crop` may not exist in any particular dictionary within `D_crops`
2. any of the lists `D_plots` or `D_crops` could be missing or just empty lists (`[]`)

In our first attempt we will ignore these problems.

```python
for farms in d:
    plot = farms['D_plots']
    for crops in plot:
        crop = crops['D_crops']
        for curr_crops in crop:
            print(curr_crops['D_curr_crop'])
```

```output
maize
maize
maize
tomatoes
vegetable
maize
maize
maize
sorghum
...
```

In this version we test if all of the keys exist. This could be extended to check that the lists are not empty.

```python
for farms in d:
    if 'D_plots' in farms :
        plot = farms['D_plots']
        for crops in plot:
            if 'D_crops' in crops :
                crop = crops['D_crops']
                for curr_crops in crop:
                    if 'D_curr_crop' in curr_crops:
                        print(curr_crops['D_curr_crop'])
```

We can now produce a list of all of the crops in all of the plots in all of the farms.

We can also create a unique set of all of the crops grown using the Python `set` data structure as shown in the code below. A set is like a list but does not allow duplicate values (but doesn’t raise an error if you try to add a duplicate).

```python
unique_crops = set()
for farms in d:
    if 'D_plots' in farms :
        plot = farms['D_plots']
        for crops in plot:
            if 'D_crops' in crops :
                crop = crops['D_crops']
                for curr_crops in crop:
                    if 'D_curr_crop' in curr_crops:
                        #print(curr_crops['D_curr_crop'])
                        unique_crops.add(curr_crops['D_curr_crop'])
print(unique_crops)
```

```output
{'peanut', 'potatoes', 'tomatoes', 'other', 'vegetable', 'amendoim', 'sunflower', 'bananas', 'sesame', None, 'cucumber', 'onion', 'sorghum', 'piri_piri', 'baby_corn', 'cabbage', 'ngogwe', 'maize', 'pigeonpeas', 'beans'}
```

Simply having a list of all of the crops is unlikely to be enough. What you are really interested in is which farm grows which crops in which plot.

We can accumulate this information as we move through the list of dictionary objects. At the top level, `farm`, there is a unique identifier `A03_quest_no` which we can use. for the plot and the crop within the plot we will create our own simple indexing system (`plot_no` and `crop_no`). At the end instead of just printing the crop name, we also print the details of where this crop is being grown.

```python
for farms in d:
    plot_no = 0
    id = farms['A03_quest_no']
    if 'D_plots' in farms :
        plot = farms['D_plots']
        for crops in plot:
            crop_no = 0
            plot_no += 1
            if 'D_crops' in crops :
                crop = crops['D_crops']
                for curr_crops in crop:
                    crop_no += 1
                    if 'D_curr_crop' in curr_crops:
                        print("Farm no ", id," grows ", curr_crops['D_curr_crop']," in plot", plot_no , " and it is crop number ", crop_no)
```

```output
Farm no 01 grows maize in plot 1 and it is crop number 1
Farm no 01 grows maize in plot 2 and it is crop number 1
Farm no 01 grows maize in plot 1 and it is crop number 1
Farm no 01 grows tomatoes in plot 2 and it is crop number 1
Farm no 01 grows vegetable in plot 3 and it is crop number 1
...
```

The final stage of this data extraction process is to save the extracted data to a file for subsequent use.

Rather than manually appending all of the information items into a string with `,` seperating each, we can use the `csv` module.

To do this we need to create a `csv.writer` object and use it to write complete rows of data at a time. `csv.writer` expects the data to be provided as a list of items.

For the header row we provide a list of strings containing the colmn names we want and at the end we proivide the data items in a list as well.

```python
import csv
filename = "SAFI_crops.csv"
fw = open(filename, 'w')
cf = csv.writer(fw, lineterminator='\n')

# write the header
cf.writerow(["Farm","plot_no","plot_area","crop_no","crop_name"])

for farms in d:
    plot_no = 0
    id = farms['A03_quest_no']
    if 'D_plots' in farms :
        plot = farms['D_plots']
        for crops in plot:
            crop_no = 0
            plot_no += 1
            if 'D_crops' in crops :
                plot_area = crops['D02_total_plot']
                crop = crops['D_crops']
                for curr_crops in crop:
                    crop_no += 1
                    if 'D_curr_crop' in curr_crops:
                        #print( id, plot_no , plot_area , crop_no, curr_crops['D_curr_crop'])
                        cf.writerow([id, plot_no , plot_area , crop_no, curr_crops['D_curr_crop']])

fw.close()
```

{% enddetails %}

{% enddetails %}

{% enddetails %}

{% details Key Points %}

- JSON is a popular data format for transferring data used by a great many Web based APIs
- The JSON data format is very similar to the Python Dictionary structure.
- The complex structure of a JSON document means that it cannot easily be ‘flattened’ into tabular data
- We can use Python code to extract values of interest and place them in a csv file

{% enddetails %}


## 5. Reading data from a file using Pandas

{% details Questions %}

- What is Pandas?
- How do I read files using Pandas?
- What is the difference between reading files using Pandas and other methods of reading files?

{% enddetails %}

{% details Objectives %}

- Explain what a module is and how they are used in Python
- Describe what the Python Data Analysis Library (pandas) is
- Load the Python Data Analysis Library (pandas)
- Use read_csv to read tabular data into Python

{% enddetails %}

{% details note What is Pandas? %}

pandas is a Python library containing a set of functions and specialised data structures that have been designed to help Python programmers to perform data analysis tasks in a structured way.

Most of the things that pandas can do can be done with basic Python, but the collected set of pandas functions and data structure makes the data analysis tasks more consistent in terms of syntax and therefore aids readabilty.

Particular features of pandas that we will be looking at over this and the next couple of episodes include:

- Reading data stored in CSV files (other file formats can be read as well)
- Slicing and subsetting data in Dataframes (tables!)
- Dealing with missing data
- Reshaping data (long -> wide, wide -> long)
- Inserting and deleting columns from data structures
- Aggregating data using data grouping facilities using the split-apply-combine paradigm
- Joining of datasets (after they have been loaded into Dataframes)

If you are wondering why I write pandas with a lower case ‘p’ it is because it is the name of the package and Python is case sensitive.

{% enddetails %}

{% details note Importing the pandas library %}

Importing the pandas library is done in exactly the same way as for any other library. In almost all examples of Python code using the pandas library, it will have been imported and given an alias of `pd`. We will follow the same convention.

```python
import pandas as pd
```

{% enddetails %}

{% details note Pandas data structures %}

There are two main data structure used by pandas, they are the Series and the Dataframe. The Series equates in general to a vector or a list. The Dataframe is equivalent to a table. Each column in a pandas Dataframe is a pandas Series data structure.

We will mainly be looking at the Dataframe.

We can easily create a Pandas Dataframe by reading a .csv file

{% enddetails %}

{% details note Reading a csv file %}

When we read a csv dataset in base Python we did so by opening the dataset, reading and processing a record at a time and then closing the dataset after we had read the last record. Reading datasets in this way is slow and places all of the responsibility for extracting individual data items of information from the records on the programmer.

The main advantage of this approach, however, is that you only have to store one dataset record in memory at a time. This means that if you have the time, you can process datasets of any size.

In Pandas, csv files are read as complete datasets. You do not have to explicitly open and close the dataset. All of the dataset records are assembled into a Dataframe. If your dataset has column headers in the first record then these can be used as the Dataframe column names. You can explicitly state this in the parameters to the call, but pandas is usually able to infer that there ia a header row and use it automatically.

For our examples in this episode we are going to use the SN7577.tab file. This is available from the [lesson data directory](https://github.com/datacarpentry/python-socialsci/tree/gh-pages/data)

We are going to read in our SN7577.tab file. Although this is a tab delimited file we will still use the pandas `read_csv` method, but we will explicitly tell the method that the separator is the tab character and not a comma which is the default.

```python
df_SN7577 = pd.read_csv("SN7577.tab", sep='\t')
```

{% details Challenge: Exercise %}

What happens if you forget to specify `sep='\t'` when reading a tab delimited dataset

```python
df_SN7577_oops = pd.read_csv("SN7577.tab")
print(df_SN7577_oops.shape)
print(df_SN7577_oops)
```

If you allow pandas to assume that your columns are separated by commas (the default) and there aren’t any, then each record will be treated as a single column. So the shape is given as 1286 rows (correct) but only one column. When the contents is display the only column name is the complete first record. Notice the `\t` used to represent the tab characters in the output. This is the same format we used to specify the tab separator when we correctly read in the file.

{% enddetails %}

{% enddetails %}

{% details note Getting information about a Dataframe %}

You can find out the type of the variable `df_SN7577` by using the `type` function.

```python
print(type(df_SN7577))
```

```output
<class 'pandas.core.frame.DataFrame'>
```

You can see the contents by simply entering the variable name. You can see from the output that it is a tabular format. The column names have been taken from the first record of the file. On the left hand side is a column with no name. The entries here have been provided by pandas and act as an index to reference the individual rows of the Dataframe.

The `read_csv()` function has an `index_col` parameter which you can use to indicate which of the columns in the file you wish to use as the index instead. As the SN7577 dataset doesn’t have a column which would uniquely identify each row we cannot do that.

Another thing to notice about the display is that it is truncated. By default you will see the first and last 30 rows. For the columns you will always get the first few columns and typically the last few depending on display space.

```python
df_SN7577
```

Similar information can be obtained with `df_SN7577.head()` But here you are only returned the first 5 rows by default.

```python
df_SN7577.head()
```

{% details Challenge: Exercise %}

1. As well as the `head()` method there is a `tail()` method. What do you think it does? Try it.
2. Both methods accept a single numeric parameter. What do you think it does? Try it.

{% enddetails %}

{% enddetails %}

{% details note Dataframe size and column metadata %}

You can obtain other basic information about your Dataframe of data with:

```python
# How many rows?
print(len(df_SN7577))
# How many rows and columns - returned as a tuple
print(df_SN7577.shape)
#How many 'cells' in the table
print(df_SN7577.size)
# What are the column names
print(df_SN7577.columns)
# what are the data types of the columns?
print(df_SN7577.dtypes)
```

```output
1286
(1286, 202)
259772
Index(['Q1', 'Q2', 'Q3', 'Q4', 'Q5ai', 'Q5aii', 'Q5aiii', 'Q5aiv', 'Q5av',
       'Q5avi',
       ...
       'numhhd', 'numkid', 'numkid2', 'numkid31', 'numkid32', 'numkid33',
       'numkid34', 'numkid35', 'numkid36', 'wts'],
      dtype='object', length=202)
Q1             int64
Q2             int64
Q3             int64
...
Length: 202, dtype: object
```

{% details Challenge: Exercise %}

When we asked for the column names and their data types, the output was abridged, i.e. we didn’t get the values for all of the columns. Can you write a small piece of code which will return all of the values

```python
for name in df_SN7577.columns:
    print(name)
```

{% enddetails %}

{% enddetails %}

{% details Key Points %}

- pandas is a Python library containing functions and data structures to assist in data analysis
- pandas data structures are the Series (like a vector) and the Dataframe (like a table)
- the pandas `read_csv` function allows you to read an entire `csv` file into a Dataframe

{% enddetails %}


## 6. Extracting row and columns

{% details Questions %}

- How can I extract specific rows and columns from a Dataframe?
- How can I add or delete columns from a Dataframe?
- How can I find and change missing values in a Dataframe?

{% enddetails %}

{% details Objectives %}

- Define indexing as it relates to data structures
- Select specific columns from a data frame
- Select specific rows from a data frame based on conditional expressions
- Using indexes to access rows and columns
- Copy a data frame
- Add columns to a data frame
- Analyse datasets having missing/null values

{% enddetails %}

We will continue this episode from where we left off in the last episode. If you have restarted Jupyter or you want to use a new notebook make sure that you import pandas and have read the SN7577.tab dataset into a Dataframe.

```python
import pandas as pd
df_SN7577 = pd.read_csv("SN7577.tab", sep='\t')
```

{% details note Selecting rows and columns from a pandas Dataframe %}

If we know which columns we want before we read the data from the file we can tell `read_csv()` to only import those columns by specifying columns either by their index number (starting at 0) as a list to the `usecols` parameter. Alternatively we can also provide a list of column names.

```python
df_SN7577_some_cols = pd.read_csv("SN7577.tab", sep='\t', usecols= [0,1,2,173,174,175])
print(df_SN7577_some_cols.shape)
print(df_SN7577_some_cols.columns)
df_SN7577_some_cols = pd.read_csv("SN7577.tab", sep='\t', usecols= ['Q1', 'Q2', 'Q3', 'sex', 'age', 'agegroups'])
print(df_SN7577_some_cols.columns)
```

```output
(1286, 6)
Index(['Q1', 'Q2', 'Q3', 'sex', 'age', 'agegroups'], dtype='object')
Index(['Q1', 'Q2', 'Q3', 'sex', 'age', 'agegroups'], dtype='object')
```

Let us assume for now that we read in the complete file which is now in the Dataframe `df_SN7577`, how can we now refer to specific columns?

There are two ways of doing this using the column names (or labels):

```python
# Both of these statements are the same
print(df_SN7577['Q1'])
# and
print(df_SN7577.Q1)
```

```python
0        1
1        3
2       10
3        9
...
```

If we are interested in more than one column, the 2nd method above cannot be used. However in the first, although we used a string with the value of `'Q1'` we could also have provided a list of strings. Remember that lists are enclosed in `[]`.

```python
print(df_SN7577[['Q1', 'Q2', 'Q3']])
```

```python
Q1  Q2  Q3
0      1  -1   1
1      3  -1   1
2     10   3   2
3      9  -1  10
...
```

What happens if you:

1. List the columns you want out of order from the way they appear in the file?
2. Put the same column name in twice?
3. Put in a non-existing column name? (a.k.a Typo)

```python
print(df_SN7577[['Q3', 'Q2']])
print(df_SN7577[['Q3', 'Q2', 'Q3']])
print(df_SN7577[['Q33', 'Q2']])
```

{% enddetails %}

{% details note Filtering by Rows %}

You can filter the Dataframe by rows by specifying a range in the form of `a:b`. `a` is the first row and `b` is one beyond the last row required.

```python
# select row with index of 1, 2 and 3 (rows 2, 3 and 4 in the Dataframe)
df_SN7577_some_rows = df_SN7577[1:4]
df_SN7577_some_rows
```

{% details Challenge: Exercise %}

What happens if we ask for a single row instead of a range?

```python
df_SN7577[1]
```

You get an error if you only specify `1`. You need to use `:1` or `0:1` to get the first row returned. The `:` is always required. You can use `:` by itself to return all of the rows.

{% enddetails %}

{% enddetails %}

{% details note Using criteria to filter rows %}

It is more likely that you will want to select rows from the Dataframe based on some criteria, such as “all rows where the value for Q2 is -1”.

```python
df_SN7577_some_rows = df_SN7577[(df_SN7577.Q2 == -1)]
df_SN7577_some_rows
```

The criteria can be more complex and isn’t limited to a single column’s values:

```python
df_SN7577_some_rows = df_SN7577[ (df_SN7577.Q2 == -1) & (df_SN7577.numage > 60)]
df_SN7577_some_rows
```

We can combine the row selection with column selection:

```python
df_SN7577_some_rows = df_SN7577[ (df_SN7577.Q2 == -1) & (df_SN7577.numage > 60)][['Q1', 'Q2','numage']]
df_SN7577_some_rows
```

Selecting rows on the row index is of limited use unless you need to select a contiguous range of rows.

There is however another way of selecting rows using the row index:

```python
df_SN7577_some_rows = df_SN7577.iloc[1:4]
df_SN7577_some_rows
```

Using the `iloc` method gives the same results as our previous example.

However, now we can specify a single value and more importantly we can use the `range()` function to indicate the records that we want. This can be useful for making pseudo-random selections of rows from across the Dataframe.

```python
# Select the first row from the Dataframe
df_SN7577_some_rows = df_SN7577.iloc[0]
df_SN7577_some_rows
# select every 100th record from the Dataframe.
df_SN7577_some_rows = df_SN7577.iloc[range(0, len(df_SN7577), 100)]
df_SN7577_some_rows
```

You can also specify column ranges using the `iloc` method again using the column index numbers:

```python
# columns 0,1,2 and 3
df_SN7577_some_rows = df_SN7577.iloc[range(0, len(df_SN7577), 100),0:4]
df_SN7577_some_rows
# columns 0,1,2,78 and 95
df_SN7577_some_rows = df_SN7577.iloc[range(0, len(df_SN7577), 100),[0,1,2,78,95]]
df_SN7577_some_rows
```

There is also a `loc` method which allows you to use the column names.

```python
# columns 0,1,2,78 and 95 using the column names and changing 'iloc' to 'loc'
df_SN7577_some_rows = df_SN7577.loc[range(0, len(df_SN7577), 100),['Q1', 'Q2', 'Q3', 'Q18bii', 'access6' ]]
df_SN7577_some_rows
```

{% enddetails %}

{% details note Sampling %}

Pandas does have a `sample` method which allows you to extract a sample of the records from the Dataframe.

```python
df_SN7577.sample(10, replace=False)             # ten records, do not select same record twice (this is the default)
df_SN7577.sample(frac=0.05, random_state=1)     # 5% of records , same records if run again
```

{% enddetails %}

{% details Key Points %}

- Import specific columns when reading in a .csv with the `usecols` parameter
- We easily can chain boolean conditions when filtering rows of a pandas dataframe
- The `loc` and `iloc` methods allow us to get rows with particular labels and at particular integer locations respectively
- pandas has a handy `sample` method which allows us to extract a sample of rows from a dataframe

{% enddetails %}


## 7. Data Aggregation using Pandas

{% details Questions %}

- How can I summarise the data in a data frame?

{% enddetails %}

{% details Objectives %}

- Access and summarize data stored in a Data Frame
- Perform basic mathematical operations and summary statistics on data in a Pandas Data Frame
- Understand missing data
- Changing to and from ‘NaN’ values

{% enddetails %}

{% details note Using Pandas functions to summarise data in a Data Frame %}

For variables which contain numerical values we are often interested in various statistical measures relating to those values. For categorical variable we are often interested in the how many of each unique values are present in the dataset.

We shall use the SAFI_results.csv dataset to demonstrate how we can obtain these pieces of information

```python
import pandas as pd
df_SAFI = pd.read_csv("SAFI_results.csv")
df_SAFI
```

For numeric variables we can obtain a variety of basic statistical information by using the `describe()` method.

```python
df_SAFI.describe()
```

This can be done for the Dataframe as a whole, in which case some of the results might have no sensible meaning. If there are any missing values, represented in the display as `NaN` you will get a warning message.

You can also `.describe()` on a single variable basis.

```python
df_SAFI['B_no_membrs'].describe()
```

There are also a set of methods which allow us to obtain individual values.

```python
print(df_SAFI['B_no_membrs'].min())
print(df_SAFI['B_no_membrs'].max())
print(df_SAFI['B_no_membrs'].mean())
print(df_SAFI['B_no_membrs'].std())
print(df_SAFI['B_no_membrs'].count())
print(df_SAFI['B_no_membrs'].sum())
```

```output
2
19
7.190839694656488
3.1722704895263734
131
942
```

Unlike the `describe()` method which converts the variable to a float (when it was originally an integer), the individual summary methods only does so for the returned result if needed.

We can do the same thing for the `E19_period_use` variable

```python
print(df_SAFI['E19_period_use'].min())
print(df_SAFI['E19_period_use'].max())
print(df_SAFI['E19_period_use'].mean())
print(df_SAFI['E19_period_use'].std())
print(df_SAFI['E19_period_use'].count())
print(df_SAFI['E19_period_use'].sum())
```

```python
1.0
45.0
12.043478260869565
8.583030848015385
92
1108.0
```

{% details Challenge: Exercise %}

Compare the count values returned for the `B_no_membrs` and the `E19_period_use` variables.

1. Why do you think they are different?
2. How does this affect the calculation of the mean values?

{% details success Solution %}

1. We know from when we originally displayed the contents of the `df_SAFI` Dataframe that there are 131 rows in it. This matches the value for the `B_no_membrs` count. The count for `E19_period_use` however is only 92. If you look at the values in the `E19_period_use` column using

```python
df_SAFI['E19_period_use']
```

you will see that there are several `NaN` values. They also occurred when we used `describe()` on the full Dataframe. `NaN` stands for Not a Number, ie. the value is missing. There are only 92 non-missing values and this is what is reported by the `count()` method. This value is also used in the calculation of the mean and std values.

{% enddetails %}

{% enddetails %}

{% enddetails %}

{% details note Dealing with missing values %}

We can find out how many variables in our Dataframe contains any `NaN` values with the code

```python
df_SAFI.isnull().sum()
```

```python
Column1                             0
A01_interview_date                  0
A03_quest_no                        0
A04_start                           0
...
```

or for a specific variable

```python
df_SAFI['E19_period_use'].isnull().sum()
```

```python
39
```

Data from most sources has the potential to include missing data. Whether or not this presents a problem at all depends on what you are planning to do.

We have been using data from two very different sources.

The SN7577 dataset is provided by the UK Data Service. Datasets from the UK data Service, have already been ‘cleaned’ and it is unlikely that there will be any genuinely missing data. However you may find that data which was missing has been replaced with a value such as ‘-1’ or ‘Not Specified’. In cases like these it may be appropriate to replace these values with ‘NaN’ before you try to process the data further.

The SAFI dataset we have been using comes from a project called ‘Studying African Farmer-led Irrigation’. The data for this project is questionnaire based, but rather than using a paper-based questionnaire, it has been created and is completed electronically via an app on a smartphone. This provides flexibility in the design and presentation of the questionnaire; a section of the questionnaire may only be presented depending on the answer given to some preceding question. This means that there can quite legitimately be a set of ‘NaN’ values in a record (one complete questionnaire) where you would still consider the record to be complete.

We have already seen how we can check for missing values. There are three other actions we need to be able to do:

1. Remove complete rows which contain `NaN`
2. Replace `NaN` with a value of our choice
3. Replace specific values with `NaN`

With these options we can ensure that the data is suitable for the further processing we have planned.

{% enddetails %}

{% details note Completely remove rows with NaNs %}

The `dropna()` method will delete all rows if any of the variables contain an `NaN`. For some datasets this may be acceptable. You will need to take care that you have enough rows left for your analysis to have meaning.

```python
df_SAFI = pd.read_csv("SAFI_results.csv")
print(df_SAFI.shape)
df_SAFI.dropna(inplace=True)
print(df_SAFI.shape)
```

```python
(131, 55)
(0, 55)
```

Because there are variables in the SAFI dataset which are all `NaN` using the `dropna()` method effectively deletes all of the rows from the Dataframe, probably not what you wanted. Instead we can use the `notnull()` method as a row selection criteria and delete the rows where a specific variable has `NaN` values.

```python
df_SAFI = pd.read_csv("SAFI_results.csv")
print(df_SAFI.shape)
df_SAFI = df_SAFI[(df_SAFI['E_no_group_count'].notnull())]
print(df_SAFI.shape)
```

```python
(131, 55)
(39, 55)
```

{% enddetails %}

{% details note Replace NaN with a value of our choice %}

The `E19_period_use` variable answers the question: “For how many years have you been irrigating the land?”. In some cases the land is not irrigated and these are represented by NaN in the dataset. So when we run

```python
df_SAFI['E19_period_use'].describe()
```

we get a count value of 92 and all of the other statistics are based on this count value.

Now supposing that instead of NaN the interviewer entered a value of 0 to indicate the land which is not irrigated has been irrigated for 0 years, technically correct.

To see what happens we can convert all of the NaN values in the `E19_period_use` column to 0 with the following code:

```python
df_SAFI['E19_period_use'].fillna(0, inplace=True)
```

If we now run the `describe()` again you can see that all of the statistic have been changed because the calculations are NOW based on a count of 131. Probably not what we would have wanted.

Conveniently this allows us to demonstrate our 3rd action.

{% enddetails %}

{% details note Replace specific values with NaN %}

Although we can recognise `NaN` with methods like `isnull()` or `dropna()` actually creating a `NaN` value and putting it into a Dataframe, requires the `numpy` module. The following code will replace our 0 values with `NaN`. We can demonstrate that this has occurred by running the `describe()` again and see that we now have our original values back.

```python
import numpy as np
df_SAFI['E19_period_use'].replace(0, np.NaN, inplace = True)
df_SAFI['E19_period_use'].describe()
```

{% enddetails %}

{% details note Categorical variables %}

For categorical variables, numerical statistics don’t make any sense. For a categorical variable we can obtain a list of unique values used by the variable by using the `unique()` method.

```python
df_SAFI = pd.read_csv("SAFI_results.csv")
pd.unique(df_SAFI['C01_respondent_roof_type'])
```

```python
array(['grass', 'mabatisloping', 'mabatipitched'], dtype=object)
```

Knowing all of the unique values is useful but what is more useful is knowing how many occurrences of each there are. In order to do this we can use the `groupby` method.

Having performed the `groupby()` we can them `describe()` the results. The format is similar to that which we have seen before except that the ‘grouped by’ variable appears to the left and there is a set of statistics for each unique value of the variable.

```python
grouped_data = df_SAFI.groupby('C01_respondent_roof_type')
grouped_data.describe()
```

You can group by more than one variable at a time by providing them as a list.

```python
grouped_data = df_SAFI.groupby(['C01_respondent_roof_type', 'C02_respondent_wall_type'])
grouped_data.describe()
```

You can also obtain individual statistics if you want.

```python
A11_years_farm = df_SAFI.groupby(['C01_respondent_roof_type', 'C02_respondent_wall_type'])['A11_years_farm'].count()
A11_years_farm
```

```python
C01_respondent_roof_type  C02_respondent_wall_type
grass                     burntbricks                 22
                          muddaub                     42
                          sunbricks                    9
mabatipitched             burntbricks                  6
                          muddaub                      3
...
```

{% details Challenge: Exercise %}

1. Read in the SAFI_results.csv dataset.
2. Get a list of the different `C01_respondent_roof_type` values.
3. Groupby `C01_respondent_roof_type` and describe the results.
4. Remove rows with NULL values for `E_no_group_count`.
5. repeat steps 2 & 3 and compare the results.

```python
# Steps 1 and 2
import numpy as np
df_SAFI = pd.read_csv("SAFI_results.csv")
print(df_SAFI.shape)
print(pd.unique(df_SAFI['C01_respondent_roof_type']))
```

```python
# Step 3
grouped_data = df_SAFI.groupby('C01_respondent_roof_type')
grouped_data.describe()
```

```python
# steps 4 and 5
df_SAFI = df_SAFI[(df_SAFI['E_no_group_count'].notnull())]
grouped_data = df_SAFI.groupby('C01_respondent_roof_type')
print(df_SAFI.shape)
print(pd.unique(df_SAFI['C01_respondent_roof_type']))
grouped_data.describe()
```

`E_no_group_count` is related to whether or not farm plots are irrigated or not. It has no obvious connection to farm buildings. By restricting the data to non-irrigated plots we have accidentally? removed one of the roof_types completely.

- Summarising numerical and categorical variables is a very common requirement
- Missing data can interfere with how statistical summaries are calculated
- Missing data can be replaced or created depending on requirement
- Summarising or aggregation can be done over single or multiple variables at the same time

{% enddetails %}

{% enddetails %}


## 8. Joining Pandas Dataframes

{% details Questions %}

- How can I join two Dataframes with a common key?

{% enddetails %}

{% details Objectives %}

- Understand why we would want to join Dataframes
- Know what is needed for a join to be possible
- Understand the different types of joins
- Understand what the joined results tell us about our data

{% enddetails %}

{% details note Why do we want to do this %}

There are many occasions when we have related data spread across multiple files.

The data can be related to each other in different ways. How they are related and how completely we can join the data from the datasets will vary.

In this episode we will consider different scenarios and show we might join the data. We will use csv files and in all cases the first step will be to read the datasets into a pandas Dataframe from where we will do the joining. The csv files we are using are cut down versions of the SN7577 dataset to make the displays more manageable.

First, let’s download the datafiles. They are listed in the setup page for the lesson. Alternatively, you can download the GitHub repository for this lesson. The data files are in the data directory. If you’re using Jupyter, make sure to place these files in the same directory where your notebook file is.

{% enddetails %}

{% details note Scenario 1 - Two data sets containing the same columns but different rows of data %}

Here we want to add the rows from one Dataframe to the rows of the other Dataframe. In order to do this we can use the `pd.concat()` function.

```python
import pandas as pd

df_SN7577i_a = pd.read_csv("SN7577i_a.csv")
df_SN7577i_b = pd.read_csv("SN7577i_b.csv")
```

Have a quick look at what these Dataframes look like with

```python
print(df_SN7577i_a)
print(df_SN7577i_b)
```

```python
  Id  Q1  Q2  Q3  Q4
0   1   1  -1   1   8
1   2   3  -1   1   4
2   3  10   3   2   6
3   4   9  -1  10  10
...

  Id  Q1  Q2  Q3  Q4
0  1277  10  10   4   6
1  1278   2  -1   5   4
2  1279   2  -1   4   5
3  1280   1  -1   2   3
...
```

The `concat()` function appends the rows from the two Dataframes to create the df_all_rows Dataframe. When you list this out you can see that all of the data rows are there, however, there is a problem with the `index`.

```python
df_all_rows = pd.concat([df_SN7577i_a, df_SN7577i_b])
df_all_rows
```

We didn’t explicitly set an index for any of the Dataframes we have used. For `df_SN7577i_a` and `df_SN7577i_b` default indexes would have been created by pandas. When we concatenated the Dataframes the indexes were also concatenated resulting in duplicate entries.

This is really only a problem if you need to access a row by its index. We can fix the problem with the following code.

```python
df_all_rows=df_all_rows.reset_index(drop=True)

# or, alternatively, there's the `ignore_index` option in the `pd.concat()` function:
df_all_rows = pd.concat([df_SN7577i_a, df_SN7577i_b], ignore_index=True)

df_all_rows
```

What if the columns in the Dataframes are not the same?

```python
df_SN7577i_aa = pd.read_csv("SN7577i_aa.csv")
df_SN7577i_bb = pd.read_csv("SN7577i_bb.csv")
df_all_rows = pd.concat([df_SN7577i_aa, df_SN7577i_bb])
df_all_rows
```

In this case `df_SN7577i_aa` has no Q4 column and `df_SN7577i_bb` has no `Q3` column. When they are concatenated, the resulting Dataframe has a column for `Q3` and `Q4`. For the rows corresponding to `df_SN7577i_aa` the values in the `Q4` column are missing and denoted by `NaN`. The same applies to `Q3` for the `df_SN7577i_bb` rows.

```python
df_SN7577i_c = pd.read_csv("SN7577i_c.csv")
df_SN7577i_d = pd.read_csv("SN7577i_d.csv")
df_all_cols = pd.concat([df_SN7577i_c, df_SN7577i_d], axis = 1)
df_all_cols
```

We use the `axis=1` parameter to indicate that it is the columns that need to be joined together. Notice that the `Id` column appears twice, because it was a column in each dataset. This is not particularly desirable, but also not necessarily a problem. However, there are better ways of combining columns from two Dataframes which avoid this problem.

{% enddetails %}

{% details note Scenario 3 - Using merge to join columns %}

We can join columns from two Dataframes using the `merge()` function. This is similar to the SQL ‘join’ functionality.

A detailed discussion of different join types is given in the SQL lesson.

You specify the type of join you want using the `how` parameter. The default is the `inner` join which returns the columns from both tables where the `key` or common column values match in both Dataframes.

The possible values of the `how` parameter are shown in the picture below (taken from the Pandas documentation)

The different join types behave in the same way as they do in SQL. In Python/pandas, any missing values are shown as `NaN`

In order to `merge` the Dataframes we need to identify a column common to both of them.

```python
df_cd = pd.merge(df_SN7577i_c, df_SN7577i_d, how='inner')
df_cd
```

In fact, if there is only one column with the same name in each Dataframe, it will be assumed to be the one you want to join on. In this example the `Id` column

Leaving the join column to default in this way is not best practice. It is better to explicitly name the column using the `on` parameter.

```python
df_cd = pd.merge(df_SN7577i_c, df_SN7577i_d, how='inner', on = 'Id')
```

In many circumstances, the column names that you wish to join on are not the same in both Dataframes, in which case you can use the `left_on` and `right_on` parameters to specify them separately.

```python
df_cd = pd.merge(df_SN7577i_c, df_SN7577i_d, how='inner', left_on = 'Id', right_on = 'Id')
```

{% details Challenge: Practice with data %}

1. Examine the contents of the `SN7577i_aa` and `SN7577i_bb` csv files using Excel or equivalent.
2. Using the `SN7577i_aa` and `SN7577i_bb` csv files, create a Dataframe which is the result of an outer join using the `Id` column to join on.
3. What do you notice about the column names in the new Dataframe?
4. Using `shift`+`tab` in Jupyter examine the possible parameters for the `merge()` function.
5. re-write the code so that the columns names which are common to both files have suffixes indicating the filename from which they come
6. If you add the parameter `indicator=True`, what additional information is provided in the resulting Dataframe?

```python
df_SN7577i_aa = pd.read_csv("SN7577i_aa.csv")
df_SN7577i_bb = pd.read_csv("SN7577i_bb.csv")
df_aabb = pd.merge(df_SN7577i_aa, df_SN7577i_bb, how='outer', on = 'Id')
df_aabb
```

```python
df_SN7577i_aa = pd.read_csv("SN7577i_aa.csv")
df_SN7577i_bb = pd.read_csv("SN7577i_bb.csv")
df_aabb = pd.merge(df_SN7577i_aa, df_SN7577i_bb, how='outer', on = 'Id',suffixes=('_aa', '_bb'), indicator = True)
df_aabb
```

{% enddetails %}

{% enddetails %}

{% details Key Points %}

- You can join pandas Dataframes in much the same way as you join tables in SQL
- The `concat()` function can be used to concatenate two Dataframes by adding the rows of one to the other.
- `concat()` can also combine Dataframes by columns but the `merge()` function is the preferred way
- The `merge()` function is equivalent to the SQL JOIN clause. ‘left’, ‘right’ and ‘inner’ joins are all possible.

{% enddetails %}


## 9. Wide and long data formats

{% details Questions %}

- What are long and Wide formats?
- Why would I want to change between them?

{% enddetails %}

{% details Objectives %}

- Explain difference between long and wide formats and why each might be used
- Illustrate how to change between formats using the `melt()` and `pivot()` methods

{% enddetails %}

{% details note Wide and long data formats %}

In the SN7577 dataset that we have been using there is a group of columns which record which daily newspapers each respondent reads. Despite the un-informative names like ‘daily1’ each column refers to a current UK daily national or local newspaper.

Whether the paper is read or not is recorded using the values of 0 or 1 as a boolean indicator. The advantage of using a column for each paper means that should a respondent read multiple newspapers, all of the required information can still be recorded in a single record.

Recording information in this wide format is not always beneficial when trying to analyse the data.

Pandas provides methods for converting data from wide to long format and from long to wide format

The SN7577 dataset does not contain a variable that can be used to uniquely identify a row. This is often referred to as a ‘primary key’ field (or column).

A dataset doesn’t need to have such a key. None of the work we have done so far has required it.

When we create a pandas Dataframe by importing a csv file, we have seen that pandas will create an index for the rows. This index can be used a bit like a key field, but as we have seen there can be problems with the index when we concatenate two Dataframes together.

In the version of SN7577 that we are going to use to demonstrate long and wide formats we will add a new variable with the name of ‘Id’ and we will restrict the other columns to those starting with the word ‘daily’.

```python
import pandas as pd
df_SN7577 = pd.read_csv("SN7577.tab", sep='\t')
```

We will create a new Dataframe with a single column of ‘Id’.

```python
# create an 'Id' column
df_papers1 = pd.DataFrame(pd.Series(range(1,1287)), index=None, columns=['Id'])
```

Using the range function, we can create values of `Id` starting with 1 and going up to 1286 (remember the second parameter to range is one past the last value used.) We have explicitly coded this value because we knew how many rows were in the dataset. If we didn’t, we could have used

```python
len(df_SN7577.index) +1
```

```python
1287
```

We will create a 2nd Dataframe, based on SN7577 but containing only the columns starting with the word ‘daily’.

There are several ways of doing this, we’ll cover the way that we have covered all of the prerequisites for. We will use the `filter` method of `pandas` with its `like` parameter.

```python
df_papers2 = df_SN7577.filter(like= 'daily')
```

The value supplied to `like` can occur anywhere in the column name to be matched (and therefore selected).

{% enddetails %}

{% details note Another way %}

If we knew the column numbers and they were all continuous we could use the `iloc` method and provide the index values of the range of columns we want.

```python
df_papers2 = df_SN7577.iloc[:,118:143]
```

To create the Dataframe that we will use, we will concatenate the two Dataframes we have created.

```python
df_papers = pd.concat([df_papers1, df_papers2], axis = 1)
print(df_papers.index)
print(df_papers.columns)
```

```python
RangeIndex(start=0, stop=1286, step=1)
Index(['Id', 'daily1', 'daily2', 'daily3', 'daily4', 'daily5', 'daily6',
       'daily7', 'daily8', 'daily9', 'daily10', 'daily11', 'daily12',
       'daily13', 'daily14', 'daily15', 'daily16', 'daily17', 'daily18',
       'daily19', 'daily20', 'daily21', 'daily22', 'daily23', 'daily24',
       'daily25'],
      dtype='object')
```

We use `axis = 1` because we are joining by columns, the default is joining by rows (`axis=0`).

{% enddetails %}

{% details note From ‘wide’ to ‘long’ %}

To make the displays more manageable we will use only the first eight ‘daily’ columns

```python

{% enddetails %}

{% details note using df_papers %}

daily_list = df_papers.columns[1:8]

df_daily_papers_long = pd.melt(df_papers, id_vars = ['Id'], value_vars = daily_list)

# by default, the new columns created will be called 'variable' which is the name of the 'daily'
# and 'value' which is the value of that 'daily' for that 'Id'. So, we will rename the columns

df_daily_papers_long.columns = ['Id','Daily_paper','Value']
df_daily_papers_long
```

We now have a Dataframe that we can `groupby`.

We want to `groupby` the `Daily_paper` and then sum the `Value`.

```python
a = df_daily_papers_long.groupby('Daily_paper')['Value'].sum()
a
```

```python
Daily_paper
daily1     0
daily2    26
daily3    52
```

{% enddetails %}

{% details note From Long to Wide %}

The process can be reversed by using the `pivot()` method. Here we need to indicate which column (or columns) remain fixed (this will become an index in the new Dataframe), which column contains the values which are to become column names and which column contains the values for the columns.

In our case we want to use the `Id` column as the fixed column, the `Daily_paper` column contains the column names and the `Value` column contains the values.

```python
df_daily_papers_wide = df_daily_papers_long.pivot(index = 'Id', columns = 'Daily_paper', values = 'Value')
```

We can change our `Id` index back to an ordinary column with

```python
df_daily_papers_wide.reset_index(level=0, inplace=True)
```

{% details Challenge: Exercise %}

1. Find out how many people take each of the daily newspapers by Title.
2. Which titles don’t appear to be read by anyone?

There is a file called Newspapers.csv which lists all of the newspapers Titles along with the corresponding ‘daily’ value

Hint: Newspapers.csv contains both daily and Sunday newspapers you can filter out the Sunday papers with the following code:

```python
df_newspapers = df_newspapers[(df_newspapers.Column_name.str.startswith('daily'))]
```

{% details success Solution %}

1. Read in Newspapers.csv file and keep only the dailies.

```python
df_newspapers = pd.read_csv("Newspapers.csv")
df_newspapers = df_newspapers[(df_newspapers.Column_name.str.startswith('daily'))]
df_newspapers
```

2. Create the df_papers Dataframe as we did before.

```python
import pandas as pd
df_SN7577 = pd.read_csv("SN7577.tab", sep='\t')
#create an 'Id' column
df_papers1 = pd.DataFrame(pd.Series(range(1,1287)),index=None,columns=['Id'])
df_papers2 = df_SN7577.filter(like= 'daily')
df_papers = pd.concat([df_papers1, df_papers2], axis = 1)
df_papers
```

3. Create a list of all of the dailies, one way would be

```python
daily_list = []
for i in range(1,26):
    daily_list.append('daily'+str(i))  
```

4. Pass the list as the `value_vars` parameter to the `melt()` method

```python
#use melt to create df_daily_papers_long  
df_daily_papers_long = pd.melt(df_papers, id_vars = ['Id'], value_vars = daily_list )
#Change the column names
df_daily_papers_long.columns = ['Id', 'Daily_paper', 'Value']
```

5. `merge` the two Dataframes with a left join, because we want all of the Newspaper Titles to be included.

```python
df_papers_taken = pd.merge(df_newspapers, df_daily_papers_long, how='left', left_on = 'Column_name',right_on = 'Daily_paper')
```

6. Then `groupby` the ‘Title’ and sum the ‘Value’

```python
df_papers_taken.groupby('Title')['Value'].sum()
```

{% enddetails %}

{% enddetails %}

{% enddetails %}

{% details Key Points %}

- The `melt()` method can be used to change from wide to long format
- The `pivot()` method can be used to change from the long to wide format
- Aggregations are best done from data in the long format.

{% enddetails %}


## 10. Data visualisation using Matplotlib

{% details Questions %}

- How can I create visualisations of my data?

{% enddetails %}

{% details Objectives %}

- Create simple plots using pandas
- Import pyplot from the matplotlib library
- Customise plots using pyplot

{% enddetails %}

{% details note Plotting in Python %}

There is a wide variety of ways to plot in Python, like many programming languages. Some do more of the design work for you and others let you customize the look of the plots and all of the little details yourself. Pandas has basic plots built into it that reduce the amount of syntax, if your data is already in a DataFrame. Matplotlib. is a Python graphical library that can be used to produce a variety of different graph types, it is fully controllable down to basic elements and includes a module `pylab` that is somewhere in between (designed to feel like MATLAB plotting, if you happen to have done that before).

The Matplotlib library can be imported using any of the import techniques we have seen. As Pandas is generally imported with `import pandas as pd`, you will find that Matplotlib is most commonly imported with `import matplotlib as plt` where ‘plt’ is the alias.

In addition to importing the library, in a Jupyter notebook environment we need to tell Jupyter that when we produce a graph, we want it to be display the graph in a cell in the notebook just like any other results. To do this we use the `%matplotlib inline` directive.

Although we are using Matplotlib in this episode, Pandas can make use of several other graphical libraries available from within Python such as ggplot2 and Seaborn. Seaborn has some very powerful features and advanced plot types. One of its most useful features is formatting.

{% enddetails %}

{% details note Plotting with Pandas %}

The Pandas library contains very tight integration with Matplotlib. There are functions in Pandas that automatically call Matplotlib functions to produce graphs.

To plot with Pandas we have to import it as we have done in past episodes. To tell Jupyter that when we produce a graph we want it to be displayed in a cell in the notebook just like any other results, we use the `%matplotlib inline` directive. Without that we need to do a `show()` command.

```python
import pandas as pd
%matplotlib inline
```

We also need data to work with loaded into a DataFrame and it’s helpful to look at a few rows to remember what’s there.

We are going to use the dataset from the setup page, `SAFI_full_shortname.csv`. For the data to load, make sure to have that file in the same folder where your Jupyter notebook is running. If the file is not in that folder, you are going to have to type the full path.

```python
df = pd.read_csv("SAFI_full_shortname.csv")
df.head()
```

Next, we can plot the a histogram of a variable.

```python
df['years_liv'].hist()
```

We can change the number of bins to make it look how we would like, for example

```python
df['years_liv'].hist(bins=20)
```

We can also specify the column as a parameter and a groupby column with the `by` keyword. there are a lot of keywords available to make it look better, we can see some of the most likely ones (as decided by Pandas developers) by using shift + tab .

Lets try `layout`, `figsize`, and `sharex`.

```python
df.hist(column='years_liv',by='village',layout=(1,3),figsize=(12,3),sharex=True)
```

{% enddetails %}

{% details note Scatter plot %}

The scatter plot requires the x and y coordinates of each of the points being plotted. We can add a third dimension as different colors with the `c` argument.

```python
df.plot.scatter(x='gps_Latitude', y='gps_Longitude', c='gps_Altitude', colormap="viridis", figsize=[4,4])
```

{% details Challenge: Exercise %}

1. Make a scatter plot of `years_farm` vs `years_liv` and color the points by `buildings_in_compound`
2. Make a bar plot of the mean number of rooms per wall type

Compare the two graphs we have just drawn. How do they differ? Are the differences significant?

{% details success Solution %}

Most importantly the data in the graphs is the same. There are cosmetic differences in the scale points in the x and y axis and in the width of the bars.

The width of the bars can be changed with a parameter in the ‘bar’ function

```python
plt.bar(range(len(s)), s, width = 0.5)   # the default width is 0.8
```

Extension: try plotting by wall and roof type?

For the scatter plot:

```python
df.plot.scatter(x = 'years_liv', y = 'years_farm', c = 'buildings_in_compound', colormap = 'viridis')
```

For the barplot: we first need to calculate the mean value of rooms per wall type, then we can make the plot.

```python
rooms_mean = df.groupby('respondent_wall_type').mean()['rooms']
rooms_mean.plot.bar()
```

{% enddetails %}

{% enddetails %}

{% enddetails %}

{% details note Boxplot %}

A boxplot provides a simple representation of a variety of statistical qualities of a single set of data values. A common use of the boxplot is to compare the statistical variations across a set of variables.

The variables can be an independent series or columns of a Dataframe using the Pandas plot method

```python
df.boxplot(by ='village',column=['buildings_in_compound'])
```

We can make it look prettier with Seaborn, much more easily than fixing components manually with Matplotlib. Seaborn is a Python data visualization library based on Matplotlib. It provides a high-level interface for drawing attractive and informative statistical graphics. Seaborn comes with Anaconda; to make it available in our Python session we need to import it.

```python
import seaborn as sns
sns.boxplot(data = df, x = 'village', y = 'buildings_in_compound')
```

We can also draw linear models in a plot using `lmplot()` from `seaborn`, e.g. for `years_farm` vs `years_liv` per `village`.

```python
sns.lmplot(x='years_farm', y='years_liv',data=df,hue='village')
```

In general, most graphs can be broken down into a series of elements which, although typically related in some way, can all exist independently of each other. This allows us to create the graph in a rather piecemeal fashion.

The labels (if any) on the x and y axis are independent of the data values being represented. The title and the legend are also independent objects within the overall graph.

In Matplotlib you create the graph by providing values for all of the individual components you choose to include. When you are ready, you call the `show` function.

Using this same approach, we can plot two sets of data on the same graph.

We will use a scatter plot to demonstrate some of the available features.

{% enddetails %}

{% details note Fine-tuning figures with Matplotlib %}

If we want to do more advanced or lower level things with our plots, we need to use Matplotlib directly, not through Pandas. First we need to import it.

{% enddetails %}

{% details note Customising our plots with Matplotlib %}

We can further customise our plots with Matplotlib directly. First we need to import it. The Matplotlib library can be imported using any of the import techniques we have seen. As Pandas is generally imported with `import pandas as pd`, you will find that `matplotlib` is most commonly imported with `import matplotlib.pyplot as plt` where `plt` is the alias. For demonstration purposes, we are going to use randomly generated data, using the NumPy library (aliased here as `np`).

```python
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Generate some date for 2 sets of points.
x1 = pd.Series(np.random.rand(20) - 0.5)
y1 = pd.Series(np.random.rand(20) - 0.5)

x2 = pd.Series(np.random.rand(20) + 0.5)
y2 = pd.Series(np.random.rand(20) + 0.5)

# Add some features
plt.title('Scatter Plot')
plt.ylabel('Range of y values')
plt.xlabel('Range of x values')

# plot the points in a scatter plot
plt.scatter(x1, y1, c='red', label='Red Range')  # 'c' parameter is the colour and 'label' is the text for the legend
plt.scatter(x2, y2, c='blue', label='Blue Range')

plt.legend(loc=4)  # the locations 1,2,3 and 4 are top-right, top-left, bottom-left and bottom-right
# Show the graph with the two sets of points
plt.show()
```

In the call to the `scatter` method, the `label` parameter values are used by the legend. The `c` or `color` parameter can be set to any color Matplotlib recognises. Full details of the available colours are available in the Matplotlib website. The markers section will tell you what markers you can use instead of the default ‘dots’. There is also an `s` (size) parameter which allows you to change the size of the marker.

{% details Challenge: Exercise %}

In the scatterplot the s parameter determines the size of the dots. s can be a simple numeric value, say s=100, which will produce dots all of the same size. However, you can pass a list of values (or a Pandas Series) to provide sizes for the individual dots. This approach is very common as it allows us to provide an extra variable worth of information on the graph.

1. Modify the code we used for the scatter plot to include a size value for each of the points in the series being plotted. (The downside is that some of the smaller dots may be completely covered by the larger dots. To try and highlight when this has happened, we can change the opacity of the dots.)
2. Find out which parameter controls the opacity of the dots (clue - it is not called opacity), add it to you code and set it > to a reasonable value.

```python
# Generate some data for 2 sets of points.
# and additional data for the sizes - suitably scaled
x1 = pd.Series(np.random.rand(20) - 0.5)
y1 = pd.Series(np.random.rand(20) - 0.5)
z1 = pd.Series(np.random.rand(20) * 200)

x2 = pd.Series(np.random.rand(20) + 0.5)
y2 = pd.Series(np.random.rand(20) + 0.5)
z2 = pd.Series(np.random.rand(20) * 200)

# Add some features
plt.title('Scatter Plot')
plt.ylabel('Range of y values')
plt.xlabel('Range of x values')

# plot the points in a scatter plot
plt.scatter(x1, y1, c='red', label='Red Range', s=z1, alpha=0.5)  # 's' parameter is the dot size
plt.scatter(x2, y2, c='blue', label='Blue Range', s=z2, alpha=0.5) # 'alpha' is the opacity

plt.legend(loc=4)
plt.show()
```

Internally the Pandas ‘plot’ method has called the ‘bar’ method of Matplotlib and provided a set of parameters, including the pandas.Series s to generate the graph.

We can use Matplotlib directly to produce a similar graph. In this case we need to pass two parameters, the number of bars we need and the Pandas Series holding the values.

Let’s redo the boxplot we did above:

```python
df.boxplot(column = 'buildings_in_compound', by = 'village')
```

The automatic title of the plot does not look good, we are missing a title for the y-axis and we do not need the extra x-axis title. We can also remove the gridlines. Let’s fix these things using functions from `plt`. Note: all the adjustments for the plot have to go into the same notebook cell together with the plot statement itself.

```python
df.boxplot(column = 'buildings_in_compound', by = 'village')
plt.suptitle('') # remove the automatic title
plt.title('Buildings in compounds per village')   # add a title
plt.ylabel('Number of buildings')   # add a y-axis title
plt.xlabel('')   # remove the x-axis title
plt.grid(None)   # remove the grid lines
```

In general most graphs can be broken down into a series of elements which, although typically related in some way, can all exist independently of each other. This allows us to create the graph in a rather piecemeal fashion. The labels (if any) on the x and y axis are independent of the data values being represented. The title and the legend are also independent objects within the overall graph. In `matplotlib` you create the graph by providing values for all of the individual components you choose to include.

{% enddetails %}

{% enddetails %}

{% details note Saving a graph %}

If you wish to save your graph as an image you can do so using the `plt.savefig()` function. The image can be saved as a pdf, jpg or png file by changing the file extension. `plt.savefig()` needs to be called at the end of all your plot statements in the same notebook cell.

```python
df.boxplot(column = 'buildings_in_compound', by = 'village')
plt.suptitle('') # remove the automatic title
plt.title('Buildings in compounds per village')   # add a title
plt.ylabel('Number of buildings')   # add a y-axis title
plt.xlabel('')   # remove the x-axis title
plt.grid(None)   # remove the grid lines
plt.savefig('safi_boxplot_buildings.pdf')   # save as pdf file
plt.savefig('safi_boxplot_buildings.png', dpi = 150)  # save as png file, some extra arguments are provided
```

In general most graphs can be broken down into a series of elements which, although typically related in some way, can all exist independently of each other. This allows us to create the graph in a rather piecemeal fashion.

The labels (if any) on the x and y axis are independent of the data values being represented. The title and the legend are also independent objects within the overall graph.

In Matplotlib you create the graph by providing values for all of the individual components you choose to include. When you are ready, you call the `show` function.

Using this same approach we can plot two sets of data on the same graph. We will use a scatter plot to demonstrate some of the available features.

{% details Challenge: Exercise %}

Revisit your favorite plot we’ve made so far, or make one with your own data then:

1. add axes labels
2. add a title
3. add a legend
4. save it in two different formats

extension: try plotting by wall and roof type!

{% enddetails %}

{% enddetails %}

{% details Key Points %}

- Graphs can be drawn directly from Pandas, but it still uses Matplotlib
- Different graph types have different data requirements
- Graphs are created from a variety of discrete components placed on a ‘canvas’, you don’t have to use them all

{% enddetails %}


## 11. Accessing SQLite Databases

{% details Questions %}

- How can I access database tables using Pandas and Python?
- What are the advantages of storing data in a database

{% enddetails %}

{% details Objectives %}

- Use the sqlite3 module to interact with a SQL database
- Access data stored in SQLite using Python
- Describe the difference in interacting with data stored as a CSV file versus in SQLite
- Describe the benefits of accessing data using a database compared to a CSV file

{% enddetails %}

{% details note Introducing the sqlite3 module %}

SQLite is a relational database system. Despite the ‘Lite’ in the name it can handle databases in excess of a Terabyte. The ‘Lite’part really relates to the fact that it is a ’bare bones’ system. It provides the mechanisms to create and query databases via a simple command line interface but not much else. In the SQL lesson we used a Firefox plugin to provide a GUI (Graphical User Interface) to the SQLite database engine.

In this lesson we will use Python code using the sqlite3 module to access the engine. We can use Python code and the sqlite3 module to create, delete and query database tables.

In practice we spend a lot of the time querying database tables.

{% enddetails %}

{% details note Pandas Dataframe v SQL table %}

It is very easy and often very convenient to think of SQL tables and pandas Dataframes as being similar types of objects. All of the data manipulations, slicing, dicing, aggragetions and joins associated with SQL and SQL tables can all be accomplished with pandas methods operating on a pandas Dataframe.

The difference is that the pandas Dataframe is held in memory within the Python environment. The SQL table can largely be on disc and when you access it, it is the SQLite database engine which is doing the work. This allows you to work with very large tables which your Python environment may not have the memory to hold completely.

A typical use case for SQLite databases is to hold large datasets, you use SQL commands from Python to slice and dice and possibly aggregate the data within the database system to reduce the size to something that Python can comfortably process and then return the results to a Dataframe.

{% enddetails %}

{% details note Accessing data stored in SQLite using Python %}

We will illustrate the use of the `sqlite3` module by connecting to an SQLite database using both core Python and also using pandas.

The database that we will use is SN7577.sqlite This contains the data from the SN7577 dataset that we have used in other lessons.

{% enddetails %}

{% details note Connecting to an SQlite database %}

The first thing we need to do is import the `sqlite3` library, We will import pandas at the same time for convenience.

```python
import sqlite3
import pandas as pd
```

We will start looking at the sqlite3 library by connecting to an existing database and returning the results of running a query.

Initially we will do this without using Pandas and then we will repreat the exercise so that you can see the difference.

The first thing we need to do is to make a connection to the database. An SQLite database is just a file. To make a connection to it we only need to use the sqlite3 `connect()` function and specify the database file as the first parameter.

The connection is assigned to a variable. You could use any variable name, but ‘con’ is quite commonly used for this purpose

```python
con = sqlite3.connect('SN7577.sqlite')
```

The next thing we need to do is to create a `cursor` for the connection and assign it to a variable. We do this using the `cursor` method of the connection object.

The cursor allows us to pass SQL statements to the database, have them executed and then get the results back.

To execute an SQL statement we use the `execute()` method of the cursor object.

The only paramater we need to pass to `execute()` is a string which contains the SQL query we wish to execute.

In our example we are passing a literal string. It could have been contained in a string variable. The string can contain any valid SQL query. It could also be a valid DDL statement such as a “CREATE TABLE …”. In this lesson however we will confine ourseleves to querying exiting database tables.

```python
cur = con.cursor()
cur.execute("SELECT * FROM SN7577")
```

```python
<sqlite3.Cursor at 0x115e10d50>
```

The `execute()` method doesn’t actually return any data, it just indicates that we want the data provided by running the SELECT statement.

{% details Challenge: Exercise %}

1. What happens if you if you ask for a non existent table?, field within a table? or just any kind of syntax error?

```python
cur = con.cursor()
# notice the mistyping of 'SELECT'
cur.execute("SELET * FROM SN7577")
```

In all cases an error message is returned. The error message is not from Python but from SQLite. It is the same error message that you would have got had you made the same errors in the SQLite plugin.

Before we can make use of the results of the query we need to use the `fetchall()` method of the cursor.

The `fetchall()` method returns a list. Each item in the list is a tuple containing the values from one row of the table. You can iterate through the items in a tuple in the same way as you would do so for a list.

```python
cur = con.cursor()
cur.execute("SELECT * FROM SN7577")
rows = cur.fetchall()
for row in rows:
    print(row)
```

```python
(1, -1, 1, 8, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 2, 3, 3, 4, 1, 4, 2, 2, 2, 2, 1, 0, 0, 0, 3, 2, 3, 3, 1, 4, 2, 3
...
```

The output is the data only, you do not get the column names.

The column names are available from the ‘description’ of the cursor.

```python
colnames = []
for description in cur.description :
    colnames.append(description[0])

print(colnames)
```

```python
['Q1', 'Q2', 'Q3', 'Q4', 'Q5ai', 'Q5aii', 'Q5aiii', 'Q5aiv', 'Q5av', 'Q5avi', 'Q5avii', 'Q5aviii', 'Q5aix', 'Q5ax', 'Q5axi', 'Q5axii', 'Q5axiii', 'Q5axiv', 'Q5axv', 'Q5bi', 'Q5bii', 'Q5biii', 'Q5biv', 'Q5bv', 'Q5bvi', 'Q5bvii', 'Q5bviii', 'Q5bix', 'Q5bx', 'Q5bxi', 'Q5bxii', 'Q5bxiii', 'Q5bxiv', 'Q5bxv', 'Q6', 'Q7a', 'Q7b', 'Q8', 'Q9', 'Q10a', 'Q10b', 'Q10c', 'Q10d', 'Q11a',
...
```

One reason for using a database is the size of the data involved. Consequently it may not be practial to use `fetchall()` as this will return the complete result of your query.

An alternative is to use the `fetchone()` method, which as the name suggestrs returns only a single row. The cursor keeps track of where you are in the results of the query, so the next call to `fetchone()` will return the next record. When there are no more records it will return ‘None’.

```python
cur = con.cursor()
cur.execute("SELECT * FROM SN7577")
row = cur.fetchone()
print(row)
row = cur.fetchone()
print(row)
```

```python
(1, -1, 1, 8, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 2, 3, 3, 4, 1, 4, 2, 2, 2, 2, 1, 0, 0, 0, 3, 2, 3, 3, 1, 4, 2, 3, 2, 4, 4, 2, 2, 2, 4, 2, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0
```

{% enddetails %}

{% details Challenge: Exercise %}

Can you write code to return the first 5 records from the SN7577 table in two different ways?

```python
import sqlite3
con = sqlite3.connect('SN7577.sqlite')
cur = con.cursor()

# we can use the SQLite 'limit' clause to restrict the number of rows returned and then use 'fetchall'
cur.execute("SELECT * FROM SN7577 Limit 5")
rows = cur.fetchall()

for row in rows:
    print(row)

# we can use 'fetchone' in a for loop
cur.execute("SELECT * FROM SN7577")
for i in range(1,6):
    print(cur.fetchone())

# a third way would be to use the 'fetchmany()' method

cur.execute("SELECT * FROM SN7577")
rows = cur.fetchmany(5)

for row in rows:
    print(row)
```

{% enddetails %}

{% enddetails %}

{% details note Using Pandas to read a database table. %}

When you use Pandas to read a database table, you connect to the database in the same way as before using the SQLite3 `connect()` function and providing the filename of the database file.

Pandas has a method `read_sql_query` to which you provide both the string containing the SQL query you wish to run and also the connection variable.

The results from running the query are placed in a pandas Dataframe with the table column names automatically added.

```python
con = sqlite3.connect('SN7577.sqlite')
df = pd.read_sql_query("SELECT * from SN7577", con)

# verify that result of SQL query is stored in the Dataframe
print(type(df))
print(df.shape)
print(df.head())

con.close()
```

{% enddetails %}

{% details note Saving a Dataframe as an SQLite table %}

There may be occasions when it is convenient to save the data in you pandas Dataframe as an SQLite table for future use or for access to other systems. This can be done using the `to_sql()` method.

```python
con = sqlite3.connect('SN7577.sqlite')
df = pd.read_sql_query("SELECT * from SN7577", con)

# select only the row where the response to Q1 is 10 meaning undecided voter
df_undecided = df[df.Q1 == 10]
print(df_undecided.shape)

# Write the new Dataframe to a new SQLite table
df_undecided.to_sql("Q1_undecided", con)

# If you want to overwrite an existing SQLite table you can use the 'if_exists' parameter
#df_undecided.to_sql("Q1_undecided", con, if_exists="replace")
con.close()
```

```python
(335, 202)
```

{% enddetails %}

{% details note Deleting an SQLite table %}

If you have created tables in an SQLite database, you may also want to delete them. You can do this by using the sqlite3 cursor `execute()` method

```python
con = sqlite3.connect('SN7577.sqlite')
cur = con.cursor()

cur.execute('drop table if exists Q1_undecided')

con.close()
```

{% details Challenge: Exercise %}

The code below creates an SQLite table as we have done in previous examples. Run this code to create the table.

```python
con = sqlite3.connect('SN7577.sqlite')
df_undecided = df[df.Q1 == 10]
df_undecided.to_sql("Q1_undecided_v2", con)
con.close()
```

Try using the following pandas code to delete (drop) the table.

```python
pd.read_sql_query("drop table Q1_undecided_v2", con)
```

1. What happens?
2. Run this line of code again, What is different?
3. Can you explain the difference and does the table now exist or not?

{% details success Solution %}

1. When the line of code is run the first time you get an error message : ‘NoneType’ object is not iterable.
2. When you run it a second time you get a different error message: DatabaseError: Execution failed on sql ‘drop table Q1_undecided_v2’: no such table: Q1_undecided_v2
3. the `read_sql_query()` method is designed to send the SQL containing your query to the SQLite execution engine, which will execute the SQL and return the output to pandas which will create a Dataframe from the results.

The SQL statement we sent is valid SQL but it doesn’t return rows from a table, it simply reports success of failure (in dropping the table in this case). The first time we run it the table is deleted and a response to the effect is returned. The resonse cannot be converted to a Dataframe, hence the first error message, which is a pandas error.

When we run it for the second time, the table has already has already been dropped, so this time the error message is from SQLite saying the table didn’t exist. Pandas recognises that this is an SQLite error message and simply passes it on to the user.

The moral of the story: pandas may be better for getting data returned into a Dataframe, but there are some things best left to the sqlite functions directly.

{% enddetails %}

{% enddetails %}

{% enddetails %}

{% details Key Points %}

- The SQLite database system is directly available from within Python
- A database table and a pandas Dataframe can be considered similar structures
- Using pandas to return all of the results from a query is simpler than using sqlite3 alone

{% enddetails %}

