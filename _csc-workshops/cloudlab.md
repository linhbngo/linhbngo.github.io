---
layout: lecture
pretty_table: true
order: 2
title: Cloud Lab
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
  - name: Setup
  - name: Introduction to Docker
  - name: Docker Images
  - name: Infrastructure as Code
  - name: "Infrastructure as Code: Storage"
  - name: "Infrastructure as Code: Networking"

---


# Introduction to CloudLab

## 1. CloudLab    
 
{% details note Overview %}



{% enddetails %}
- Visit [CloudLab's website](https://cloudlab.us)
- Click "Request an Account" 
- Fill in the information as shown in the following figure and click "Submit Request"
- Wait for a confirm
ation email to arrive in your wcupa.edu mailbox. You might have to 
resubmit a new request if you don't see this email in about half an hour. 

{% include figure.liquid path="fig/cloudlab/01.png" alt="Account creation forms" %}

- After your account is confirmed, the instructor will be able to see your application 
and can grant you access to CloudLab. 
- If you already had a CloudLab account, you can select `Start/Join Project` under
your username, then select `Join Existing Project` and provide the name `SecureEDU`. 

```

## 2. Setup SSH

{% details note Command line terminal software %}



{% enddetails %}
- Download and install [Windows Terminal from the Microsoft Store](https://www.microsoft.com/en-us/p/windows-terminal/9n0dx20hk701?activetab=pivot:overviewtab).

```

{% details note Command line terminal software on Mac %}



{% enddetails %}
- Use the Search box (magnifying glass on top-right of your Mac Desktop) and 
type in the word `Terminal`. 
- Launch the resulting Terminal app. 

```

{% details note SSH setup %}



{% enddetails %}
- First, you need to check to see if you already have SSH key. If you have done `csc231` or are working 
in classes using GitHub classroom, it is likely that you already setup your SSH keys. 
  - Run the following command

```bash
cat ~/.ssh/id_rsa.pub
```

- If you have the SSH keys, you will see the following:

{% include figure.liquid path="fig/cloudlab/04.png" alt="Public key generated" %}

:::{admonition} No SSH Key


- Launch your terminal (Windows Terminal or Mac) and run the following command: 
- Hit `Enter` for all questions. **Do not enter a password or change the default location of the files**. 

```bash
cd
ssh-keygen -t rsa
```

{% include figure.liquid path="fig/cloudlab/03.png" alt="Generate SSH keys" %}

- Run the following command to display the public key

```bash
cat ~/.ssh/id_rsa.pub
```

{% include figure.liquid path="fig/cloudlab/04.png" alt="Public key generated" %}

:::

- Drag your mouse over to paint/copy the key (just the text, no extra spaces after the last 
character)
- Log into CloudLab, click on your username (top right) and select `Manage SSH Keys`:

{% include figure.liquid path="fig/cloudlab/05.png" alt="Manage SSH Keys box" %}

- Paste the key into the `Key` box and click `Add Key`: 

{% include figure.liquid path="fig/cloudlab/06.png" alt="Paste SSH keys" %}

```



## 3. CloudLab Profiles and Experiments

{% details note Profile creation and experiment instantiation %}



{% enddetails %}
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

