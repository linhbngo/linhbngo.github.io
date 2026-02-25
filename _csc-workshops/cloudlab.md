
# Introduction to CloudLab

## 1. CloudLab    
 
???note Overview


- Visit [CloudLab's website](https://cloudlab.us)
- Click "Request an Account" 
- Fill in the information as shown in the following figure and click "Submit Request"
- Wait for a confirm
ation email to arrive in your wcupa.edu mailbox. You might have to 
resubmit a new request if you don't see this email in about half an hour. 

![Account creation forms](fig/cloudlab/01.png)

- After your account is confirmed, the instructor will be able to see your application 
and can grant you access to CloudLab. 
- If you already had a CloudLab account, you can select `Start/Join Project` under
your username, then select `Join Existing Project` and provide the name `SecureEDU`. 

```

## 2. Setup SSH

???note Command line terminal software 

 
- Download and install [Windows Terminal from the Microsoft Store](https://www.microsoft.com/en-us/p/windows-terminal/9n0dx20hk701?activetab=pivot:overviewtab).

```

???note Command line terminal software on Mac


- Use the Search box (magnifying glass on top-right of your Mac Desktop) and 
type in the word `Terminal`. 
- Launch the resulting Terminal app. 

```

???note SSH setup


- First, you need to check to see if you already have SSH key. If you have done `csc231` or are working 
in classes using GitHub classroom, it is likely that you already setup your SSH keys. 
  - Run the following command

~~~bash
cat ~/.ssh/id_rsa.pub
~~~

- If you have the SSH keys, you will see the following:

![Public key generated](fig/cloudlab/04.png)

:::{admonition} No SSH Key


- Launch your terminal (Windows Terminal or Mac) and run the following command: 
- Hit `Enter` for all questions. **Do not enter a password or change the default location of the files**. 

~~~bash
cd
ssh-keygen -t rsa
~~~

![Generate SSH keys](fig/cloudlab/03.png)

- Run the following command to display the public key

~~~bash
cat ~/.ssh/id_rsa.pub
~~~

![Public key generated](fig/cloudlab/04.png)

:::

- Drag your mouse over to paint/copy the key (just the text, no extra spaces after the last 
character)
- Log into CloudLab, click on your username (top right) and select `Manage SSH Keys`:

![Manage SSH Keys box](fig/cloudlab/05.png)

- Paste the key into the `Key` box and click `Add Key`: 

![Paste SSH keys](fig/cloudlab/06.png)

```



## 3. CloudLab Profiles and Experiments

???note Profile creation and experiment instantiation


- Login to your CloudLab account, click `Experiments` on top left, 
select `My Profiles`. 
- Click on `Project Profiles` tab
- Find and select the `SEEDLab` profile 
- Click `Instantiate` from the `seed-software` branch. 
  - Click `Next` on `Select a Profile`. 
  - Click `Next` on `Parameterize`, unless you want to change the password
  - On `Finalize`:
    - For `Name`, provide your WCUPA username
    - If you have a dropdown option on Project, select `SecureEDU`. Don't worry 
    about it if you don't have one. 
    - For `Cluster`, select `Emulab`
    - Then click `Next`
  - On `Schedule`, don't do anything, just click `Finish`. 
- You need to wait until the `State` become `Ready` **and** under the `List View` tab, `Startup` becomes `Finished`. 
- You can use the command under the `SSH command` box to log into your experiment. 
- Run `sudo su - seed` to become the `seed` user. 

```

