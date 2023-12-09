import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:workout_flutter_app/data/main.dart';
import 'package:workout_flutter_app/pages/workout_page.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {

  //text controller
     final newWorkoutNameController=TextEditingController();


  //create a new workout
   void createNewWorkout(){
      showDialog(context: context ,
                 builder: (context)=>AlertDialog(
                    title: Text('Create new Workout'),
                    content: TextField(
                        controller: newWorkoutNameController,
                    ),
                    actions: [
                      // save button
                        MaterialButton(
                          onPressed:save,
                        child: Text("Save")
                        ),
                      //cancel button
                      MaterialButton(
                        onPressed:cancel,
                        child: Text("Cancel"),)
                    ],),
      );
   }

   // go to newWorkout page
     void gotoNewWorkoutPage(String workoutName){
        Navigator.push(context, MaterialPageRoute(builder: (context)=> WorkoutPage(
          workoutName: workoutName,
        )));
     }

   //Save workout
   void save (){
     // get workout name from text controller
     String newWorkoutName=newWorkoutNameController.text;
     //add workout to workoutdata list
     Provider.of<WorkoutData>(context,listen: false).addWorkout(newWorkoutName);
     //pop dialogue box
     Navigator.pop(context);
     clear();
   }
   //cancel workout
   void cancel(){}

   //clear controller
   void clear(){
     newWorkoutNameController.clear();
   }

  @override
  Widget build(BuildContext context) {
    return Consumer<WorkoutData>(builder: (context,value, child )=> Scaffold(
      appBar: AppBar(
          title: Text('WORKOUT APP')
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: createNewWorkout,
        child: const Icon(Icons.add),),
      body: ListView.builder(
          itemCount:value.getWorkoutList().length,
          itemBuilder: (context,index) => ListTile(
            title:Text(value.getWorkoutList()[index].name),
            trailing: IconButton(onPressed:() => gotoNewWorkoutPage(value.getWorkoutList()[index].name), icon: Icon(Icons.arrow_forward_ios)),
          )),
    )
    );

  }
}




