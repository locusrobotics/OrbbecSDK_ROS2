^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package orbbec_description
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Forthcoming
-----------
* Updates the locus branch to v2.6.3 from Orbbec (`#22 <https://github.com/locusrobotics/OrbbecSDK_ROS2/issues/22>`_)
  This was tested on a robot with the overnight stress test
  ---------
  Co-authored-by: jj <957713278@qq.com>
  Co-authored-by: datean <datean@orbbec.com>
  Co-authored-by: yalian <yalian@example.com>
  Co-authored-by: xiexun <xiexun@orbbec.com>
  Co-authored-by: obyalian <yalian@orbbec.com>
  Co-authored-by: slz <shenlanzhou@orbbec.com>
  Co-authored-by: Christian Rauch <Christian.Rauch@unileoben.ac.at>
  Co-authored-by: ob-yalian <luotao2025@163.com>
* [APG-1777] change camera origin (`#21 <https://github.com/locusrobotics/OrbbecSDK_ROS2/issues/21>`_)
  Camera origin currently on outside of glass, this moves it in based on
  the dimensions from orbbec datasheet.
  Made
  [this](https://locusrobotics.atlassian.net/jira/software/projects/APG/boards/153?jql=assignee%20%3D%20712020%3A11468fc1-984e-4740-a109-f6f26005009e&selectedIssue=APG-2140)
  ticket to go through the urdf more thoroughly and add docs on where the
  values came from. This PR is just to get gazebo working asap
* Contributors: Sushant Raj, matthewkazan-locus

999.2.0 (2025-12-05)
--------------------

999.1.3 (2025-12-01)
--------------------

999.1.2 (2025-12-01)
--------------------
* Update locus branch by pulling in v2_main (with a few adjustments to keep our changes) (`#17 <https://github.com/locusrobotics/OrbbecSDK_ROS2/issues/17>`_)
* Contributors: Sushant Raj

2.4.7 (2025-09-01)
------------------
* Add Gemini 335Le in orbbec_description
* Contributors: jj

2.4.5 (2025-07-04)
------------------
* Add .camke-format.py and format CMakeLists.txt
* Update orbbec_description
* Contributors: jj

2.4.3 (2025-05-22)
------------------

2.3.4 (2025-04-21)
------------------

2.2.4 (2025-02-28)
------------------

2.2.3 (2025-02-15)
------------------

2.1.1 (2024-12-24)
------------------
* update gemini camera's urdf
* chore: Add rviz config
* Merge pull request #54 from Danilrivero/main
  Implement the femto_bolt.urdf.xacro description
* Implement the femto_bolt.urdf.xacro description
* chore: add license
* Contributors: Joe Dong, danil.rivero, datean

1.5.8 (2024-06-22)
------------------
* Merge pull request #41 from Kashery/main
  fix CMakeLists.txt at orbbec_description
* fix CMakeLists.txt at orbbec_description
  fixes build error caused by referencing a non existent rviz directory
* Add gemini 335 336 urdf
* Contributors: Joe Dong, Karol Szychulski

1.5.7 (2024-06-05)
------------------

1.5.5 (2024-05-22)
------------------

1.5.4 (2024-05-15)
------------------

1.5.2 (2024-05-12)
------------------

1.4.6 (2024-02-26)
------------------

1.4.4 (2024-01-15)
------------------

1.4.2 (2023-12-06)
------------------

1.4.1 (2023-11-23)
------------------

1.3.9 (2023-10-25)
------------------

1.3.8 (2023-10-17)
------------------

1.3.7 (2023-10-11)
------------------

1.3.6 (2023-10-07)
------------------

1.3.5 (2023-09-15 16:54)
------------------------

1.3.4 (2023-09-15 15:11)
------------------------

1.3.2 (2023-09-13)
------------------

1.2.9 (2023-08-23)
------------------
* remove lfs
* Contributors: Joe Dong

1.2.4 (2023-04-28)
------------------

1.2.1 (2023-02-20)
------------------

1.0.4 (2022-07-07)
------------------

1.0.3 (2022-07-04 17:05)
------------------------

1.0.2 (2022-07-04 16:52)
------------------------
* Merge branch 'release/1.0.1' into 'master'
  add more config
  See merge request OrbbecSDK/orbbecros2sdk!2
* update dir structure
* start orbbec_desctription
* Contributors: Joe Dong, 默存

1.0.0 (2022-06-10)
------------------
