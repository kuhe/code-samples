Code Sample (C#)


ActiveRecord overlay for Visual C# Entity Framework
==================

Define new class. Just add a method Initialize that sets the Model (DbSet<TEntity>) and the context.

    public partial class Score : ActiveRecord<Score>
    {
        protected override void Initialize()
        {
            SetModel(new FlashCardEntities().Scores);
            SetDb(new FlashCardEntities());
        }
    }
    
Subsequently, 

Score s = Scores.Get(); // get all
Score s = Scores.Get(2); // get by id
Score s = Scores.Get(x => x.UserName == "Student"); // get by lambda
Score s = Scores.GetOne(x => x.StudentAnswer == 64); // GetOne convenience method

s.save(); // update or insert at any time
s.Id = null; // nullable Id for row duplication inserts
s.save(); // creates new row and s.Id is now the new insert Id (Actually I'm not sure that part works yet)
