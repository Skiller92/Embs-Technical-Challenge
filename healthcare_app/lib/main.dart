import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:workout_flutter_app/data/main.dart';
import 'package:workout_flutter_app/pages/fetchingdata.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});


  @override
  Widget build(BuildContext context) {
    return ChangeNotifierProvider(
      create: (context) => WorkoutData(),
      child: const MaterialApp(
        debugShowCheckedModeBanner: false,
        home: HomePage(),
      ),);
  }
}


